
import sys
from pyspark.sql import SparkSession

if __name__ == "__main__":
    
    spark = SparkSession.builder.getOrCreate()
    
    house_price_dataset = spark\
    .read\
    .option("inferSchema", "true")\
    .option("header", "true")\
    .csv("hdfs:///user/kaggle/kaggle_data/bucharest_housing_prices/house_offers.csv")
    
    house_price_dataset.createOrReplaceTempView("HousePriceDataset")
    
    query = spark.sql("""
    SELECT location_area
    FROM HousePriceDataset
    """)
    
    query.show()
    