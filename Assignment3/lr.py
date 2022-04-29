
from pyspark.sql import SparkSession
from pyspark.ml.feature import VectorAssembler
from pyspark.ml.feature import StringIndexer
from pyspark.ml.feature import OneHotEncoder
from pyspark.ml.regression import LinearRegression
from pyspark.sql.functions import col, isnan, when, count
from pyspark.sql import functions as F
import pandas as pd
from sklearn.impute import KNNImputer

#! longitude,
#! latitude,
# ? housing_median_age,
# ? total_rooms,
# ? total_bedrooms,
# ? population,
# !households,
# !median_income,
# todo median_house_value,
# ? ocean_proximity


def df_spark_to_pandas(spark_df):
    pandas_df = spark_df.select("*").toPandas()
    return pandas_df


def split_training_test(data_to_split):
    splits = data_to_split.randomSplit([0.7, 0.3])
    train_df = splits[0]
    test_df = splits[1]
    return train_df, test_df


def index_ocean_proximity(house_price_df):
    #  numeric indexing for the strings (indexing starts from 0)
    indexer = StringIndexer(inputCol="ocean_proximity",
                            outputCol="ocean_proximity_index")
    #  fit the indexer model and use it to transform the strings into numeric indices
    house_price_df = indexer.fit(house_price_df).transform(house_price_df)
    house_price_df = house_price_df.drop("ocean_proximity")
    return house_price_df


def one_hot_encode(house_price_df):
    #  one-hot-encoding the numeric indices
    one_hot_encoder = OneHotEncoder(
        inputCol="ocean_proximity_index", outputCol="ocean_proximity_OHE")
    #  fit the ohe model and use it to transform the numeric indices into ohe vectors
    house_price_df = one_hot_encoder.fit(
        house_price_df).transform(house_price_df)
    return house_price_df


def create_feature_vector(house_price_df):
    vectorAssembler = VectorAssembler(inputCols=[
        "housing_median_age",
        "total_rooms",
        "total_bedrooms",
        "population",
        "ocean_proximity_index"],
        outputCol='features')
    feature_vector_df = vectorAssembler.transform(house_price_df)
    feature_vector_df = feature_vector_df.select(
        ['features', 'median_house_value'])
    return feature_vector_df


def show_null_counts(dataframe):
    dataframe.select([count(when(isnan(c) | col(c).isNull(), c)).alias(c)
                     for c in dataframe.columns]).show()


def apply_knn_imputer(pandas_df):
    imputer = KNNImputer(n_neighbors=10)
    knn_imputed_matrix = imputer.fit_transform(pandas_df)
    corrected_df = pd.DataFrame(knn_imputed_matrix, columns=[
        "housing_median_age",
        "total_rooms",
        "total_bedrooms",
        "population",
        "median_house_value",
        "ocean_proximity_index"])
    return corrected_df


def remove_NULL_values(house_price_df):
    print("NULL counts BEFORE removal")
    show_null_counts(house_price_df)
    pandas_df = df_spark_to_pandas(house_price_df)
    pandas_df = apply_knn_imputer(pandas_df)
    house_price_df = spark.createDataFrame(pandas_df)
    print("NULL counts AFTER removal")
    show_null_counts(house_price_df)
    return house_price_df


def rm_oor_operations(house_price_df, col_to_correct, lower_bound, upper_bound):
    sdf = df_spark_to_pandas(house_price_df)
    print(f"\n\n\n\nout_of_range_{col_to_correct}", col_to_correct)

    out_of_range = house_price_df.filter(
        ~col(col_to_correct).between(lower_bound, sdf[col_to_correct].mean() + upper_bound))
    out_of_range.show()

    print((out_of_range.count(), len(out_of_range.columns)))
    house_price_df = house_price_df.withColumn(col_to_correct, when(
        ~col(col_to_correct).between(lower_bound, sdf[col_to_correct].mean() + upper_bound), None).otherwise(col(col_to_correct)))
    return house_price_df


def rm_out_of_range_all(house_price_df):
    sdf = df_spark_to_pandas(house_price_df)
    print(sdf.describe(include='all'))

    print("NULL counts BEFORE range correction")
    show_null_counts(house_price_df)
    house_price_df = rm_oor_operations(
        house_price_df, "housing_median_age", 0, 2 * sdf['housing_median_age'].std())
    house_price_df = rm_oor_operations(
        house_price_df, "total_rooms", 0, 4 * sdf['total_rooms'].std())
    house_price_df = rm_oor_operations(
        house_price_df, "total_bedrooms", 0, 4 * sdf['total_bedrooms'].std())
    house_price_df = rm_oor_operations(
        house_price_df, "population", 0, 4 * sdf['population'].std())
    print("NULL counts AFTER range correction")
    show_null_counts(house_price_df)
    return house_price_df


if __name__ == "__main__":

    # creates an instance of a spark session
    spark = SparkSession.builder.getOrCreate()
    spark.sparkContext.setLogLevel('OFF')
    pd.options.display.max_columns = None
    pd.options.display.max_rows = 100

    # reads dataset from file in HDFS to a spark dataframe
    house_price_df = spark\
        .read\
        .option("inferSchema", "true")\
        .option("header", "true")\
        .csv("hdfs:///user/kaggle/kaggle_data/california_housing.csv")

    cols_to_remove = ("longitude", "latitude", "households", "median_income")
    house_price_df = house_price_df.drop(*cols_to_remove)

    # --------------------------- Categorical Indexing --------------------------- #
    house_price_df = index_ocean_proximity(house_price_df)
    # house_price_df.show()


    # ------------------ Replacing Out Of Range Values With NULL ----------------- #
    house_price_df = rm_out_of_range_all(house_price_df)


    # --------------------------- Removing NULL Values --------------------------- #
    house_price_df = remove_NULL_values(house_price_df)
    # house_price_df.show()


    # ----------------------------- One Hot Encoding ----------------------------- #
    # house_price_df = one_hot_encode(house_price_df)
    # house_price_df.show()


    # ------------------------- Feature Vector Assembler ------------------------- #
    feature_vector_df = create_feature_vector(house_price_df)
    # feature_vector_df.show()


    train_df, test_df = split_training_test(feature_vector_df)


    lr = LinearRegression(featuresCol='features', labelCol='median_house_value')
    lr_model = lr.fit(train_df)
    print("Coefficients: " + str(lr_model.coefficients))
    print("Intercept: " + str(lr_model.intercept))
