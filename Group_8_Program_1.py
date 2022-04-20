
from pyspark.sql import SparkSession

if __name__ == "__main__":
    
    # creates an instance of a spark session
    spark = SparkSession.builder.getOrCreate()
    
    # reads dataset from file in HDFS to a spark dataframe
    house_price_dataset = spark\
    .read\
    .option("inferSchema", "true")\
    .option("header", "true")\
    .csv("hdfs:///user/kaggle/kaggle_data/california_housing.csv")
    
    # creates a SQL table from the dataframe so we can perform queries on the dataset
    house_price_dataset.createOrReplaceTempView("HousePriceDataset")
    
    # queries the dataframe using raw sql
    query = spark.sql("""
    SELECT AVG(median_house_value), ocean_proximity
    FROM HousePriceDataset
    GROUP BY ocean_proximity
    """)
    
    query.show()
    print("RAW SQL OUTPUT\n\n\n")
    
    # saves query to output file
    query.coalesce(1).write.csv("hdfs:///user/phague/sql_query")
    

    