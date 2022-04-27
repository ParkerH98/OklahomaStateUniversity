
from pyspark.sql import SparkSession
from pyspark.sql import functions as F
from pyspark.sql import DataFrameWriter as W

from pyspark.ml.feature import VectorAssembler

from pyspark.ml.feature import StringIndexer
from pyspark.ml.feature import OneHotEncoder
from pyspark.ml.regression import LinearRegression

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

    #  numeric indexing for the strings (indexing starts from 0)
    indexer = StringIndexer(inputCol="ocean_proximity",
                            outputCol="ocean_proximity_index")
    #  fit the indexer model and use it to transform the strings into numeric indices
    house_price_df = indexer.fit(house_price_df).transform(house_price_df)
    house_price_df.show()
    # ---------------------------------------------------------------------------- #

    # ----------------------------- One Hot Encoding ----------------------------- #

    #  one-hot-encoding the numeric indices
    # ohe = OneHotEncoder(inputCol="ocean_proximity_index",
    #                     outputCol="ocean_proximity_OHE_vector")

    #  fit the ohe model and use it to transform the numeric indices into ohe vectors
    # house_price_df = ohe.fit(house_price_df).transform(house_price_df)
    # ---------------------------------------------------------------------------- #

    # house_price_df.printSchema()

    vectorAssembler = VectorAssembler(inputCols=['longitude', 'latitude', 'housing_median_age', 'total_rooms', 'total_bedrooms',
                                      'population', 'households', 'median_income', 'median_house_value', 'ocean_proximity_index'], outputCol='features')
    vhouse_df = vectorAssembler.transform(house_price_df)
    vhouse_df = vhouse_df.select(['features', 'median_house_value'])
    vhouse_df.show()

    splits = vhouse_df.randomSplit([0.7, 0.3])
    train_df = splits[0]
    test_df = splits[1]

    lr = LinearRegression(featuresCol='features', labelCol='median_house_value')
    lr_model = lr.fit(train_df)
    print("Coefficients: " + str(lr_model.coefficients))
    print("Intercept: " + str(lr_model.intercept))
