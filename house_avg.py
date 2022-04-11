
import sys
from pyspark.sql import SparkSession
from pyspark.sql import functions as F

if __name__ == "__main__":
    
    spark = SparkSession.builder.getOrCreate()
    
    house_price_dataset = spark\
    .read\
    .option("inferSchema", "true")\
    .option("header", "true")\
    .csv("hdfs:///user/kaggle/kaggle_data/bucharest_housing_prices/house_offers.csv")
    
    house_price_dataset.createOrReplaceTempView("HousePriceDataset")
    
    query = spark.sql("""
    SELECT AVG(price), location_area
    FROM HousePriceDataset
    GROUP BY location_area
    """)

    query.show()

    spark_query = house_price_dataset.groupBy("location_area").agg(F.mean("price")).show()
    
    