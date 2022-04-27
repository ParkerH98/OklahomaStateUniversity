
from pyspark.sql import SparkSession
from pyspark.sql import functions as F
from pyspark.sql import DataFrameWriter as W

from pyspark.ml.feature import VectorAssembler



if __name__ == "__main__":
    
    # creates an instance of a spark session
    spark = SparkSession.builder.getOrCreate()
    
    # reads dataset from file in HDFS to a spark dataframe
    house_price_df = spark\
    .read\
    .option("inferSchema", "true")\
    .option("header", "true")\
    .csv("hdfs:///user/kaggle/kaggle_data/california_housing.csv")
    
    
    house_price_df.printSchema()
    
    vectorAssembler = VectorAssembler(inputCols = ['longitude', 'latitude', 'housing_median_age', 'total_rooms', 'total_bedrooms', 'population', 'households', 'median_income', 'median_house_value', 'ocean_proximity'], outputCol = 'features')
    vhouse_df = vectorAssembler.transform(house_price_df)
    vhouse_df = vhouse_df.select(['features', 'median_house_value'])
    vhouse_df.show()
    
    # queires the dataframe using spark sql functions
    # spark_query = house_price_dataset.groupBy("ocean_proximity").agg(F.mean("median_house_value"))
    # spark_query.show()
    # print("SPARK OUTPUT\n\n\n")
    
    # saves query to output file
    # spark_query.coalesce(1).write.csv("hdfs:///user/phague/spark_query")
    