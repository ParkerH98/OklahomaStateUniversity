
import sys
from pyspark.sql import SparkSession
from pyspark.sql import functions as F


# SQL OUTPUT
# +-----------------------+---------------+
# |avg(median_house_value)|ocean_proximity|
# +-----------------------+---------------+
# |               380440.0|         ISLAND|
# |     249433.97742663656|     NEAR OCEAN|
# |     259212.31179039303|       NEAR BAY|
# |     240084.28546409807|      <1H OCEAN|
# |     124805.39200122119|         INLAND|
# +-----------------------+---------------+

# SPARK SQL OUTPUT
# |avg(median_house_value)|ocean_proximity|
# +-----------------------+---------------+
# |               380440.0|         ISLAND|
# |     249433.97742663656|     NEAR OCEAN|
# |     259212.31179039303|       NEAR BAY|
# |     240084.28546409807|      <1H OCEAN|
# |     124805.39200122119|         INLAND|
# +-----------------------+---------------+

if __name__ == "__main__":
    
    spark = SparkSession.builder.getOrCreate()
    
    house_price_dataset = spark\
    .read\
    .option("inferSchema", "true")\
    .option("header", "true")\
    .csv("hdfs:///user/kaggle/kaggle_data/california_housing.csv")
    
    house_price_dataset.createOrReplaceTempView("HousePriceDataset")
    
    query = spark.sql("""
    SELECT AVG(median_house_value), ocean_proximity
    FROM HousePriceDataset
    GROUP BY ocean_proximity
    """)

    query.show()

    spark_query = house_price_dataset.groupBy("ocean_proximity").agg(F.mean("median_house_value")).show()
    