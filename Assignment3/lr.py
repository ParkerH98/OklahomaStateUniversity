
from pyspark.sql import SparkSession
from pyspark.ml.feature import VectorAssembler
from pyspark.ml.feature import StringIndexer
from pyspark.ml.feature import OneHotEncoder
from pyspark.ml.regression import LinearRegression
from pyspark.sql.functions import col, isnan, when, count
import pandas as pd
from sklearn.impute import KNNImputer


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
    indexer = StringIndexer(inputCol="ocean_proximity", outputCol="ocean_proximity_index")
    #  fit the indexer model and use it to transform the strings into numeric indices
    house_price_df = indexer.fit(house_price_df).transform(house_price_df)
    house_price_df = house_price_df.drop("ocean_proximity")
    return house_price_df

def one_hot_encode(house_price_df):
    #  one-hot-encoding the numeric indices
    one_hot_encoder = OneHotEncoder(inputCol="ocean_proximity_index", outputCol="ocean_proximity_OHE")
    #  fit the ohe model and use it to transform the numeric indices into ohe vectors
    house_price_df = one_hot_encoder.fit(house_price_df).transform(house_price_df)
    return house_price_df

def create_feature_vector(house_price_df):
    vectorAssembler = VectorAssembler(inputCols=['longitude', 'latitude', 'housing_median_age', 'total_rooms', 'total_bedrooms',
                                      'population', 'households', 'median_income', 'ocean_proximity_index'], outputCol='features')
    feature_vector_df = vectorAssembler.transform(house_price_df)
    feature_vector_df = feature_vector_df.select(['features', 'median_house_value'])
    return feature_vector_df

def show_null_counts(dataframe):
    dataframe.select([count(when(isnan(c) | col(c).isNull(), c)).alias(c) for c in dataframe.columns]).show()

def apply_knn_imputer(pandas_df):
    imputer = KNNImputer(n_neighbors=10)
    knn_imputed_matrix = imputer.fit_transform(pandas_df)
    corrected_df = pd.DataFrame(knn_imputed_matrix, columns=["longitude",
                                  "latitude",
                                  "housing_median_age",
                                  "total_rooms",
                                  "total_bedrooms",
                                  "population",
                                  "households",
                                  "median_income",
                                  "median_house_value",
                                  "ocean_proximity"])
    return corrected_df

def remove_NULL_values(house_price_df):
    show_null_counts(house_price_df)
    pandas_df = df_spark_to_pandas(house_price_df)
    pandas_df = apply_knn_imputer(pandas_df)
    house_price_df = spark.createDataFrame(pandas_df)
    show_null_counts(house_price_df)
    return house_price_df


if __name__ == "__main__":

    # creates an instance of a spark session
    spark = SparkSession.builder.getOrCreate()

    # reads dataset from file in HDFS to a spark dataframe
    house_price_df = spark\
        .read\
        .option("inferSchema", "true")\
        .option("header", "true")\
        .csv("hdfs:///user/kaggle/kaggle_data/california_housing.csv")


    # --------------------------- Categorical Indexing --------------------------- #
    house_price_df = index_ocean_proximity(house_price_df)
    house_price_df.show()
    
    # --------------------------- Removing NULL Values --------------------------- #
    house_price_df = remove_NULL_values(house_price_df)    
    

    # ----------------------------- One Hot Encoding ----------------------------- #
    # house_price_df = one_hot_encode(house_price_df)
    # house_price_df.show()

    # ------------------------- Feature Vector Assembler ------------------------- #
    feature_vector_df = create_feature_vector(house_price_df)
    # feature_vector_df.show()


    train_df, test_df = split_training_test(feature_vector_df)

    # lr = LinearRegression(featuresCol='features',
    #                       labelCol='median_house_value')
    # lr_model = lr.fit(train_df)
    # print("Coefficients: " + str(lr_model.coefficients))
    # print("Intercept: " + str(lr_model.intercept))



