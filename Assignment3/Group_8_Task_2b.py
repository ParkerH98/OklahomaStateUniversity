from pyspark.mllib.tree import RandomForest
from pyspark.sql import SparkSession
from pyspark.ml.feature import VectorAssembler
from pyspark.ml.feature import StringIndexer

spark = SparkSession.builder.getOrCreate()
    
    # reads dataset from file in HDFS to a spark dataframe
house_price_df = spark\
    .read\
    .option("inferSchema", "true")\
    .option("header", "true")\
    .csv("hdfs:///user/kaggle/kaggle_data/california_housing.csv")

indexer = StringIndexer(inputCol="ocean_proximity",
                        outputCol="ocean_proximity_index")
house_price_df = indexer.fit(house_price_df).transform(house_price_df)

vectorAssembler = VectorAssembler(inputCols=['longitude', 'latitude', 'housing_median_age', 'total_rooms', 'total_bedrooms',
                                  'population', 'households', 'median_income', 'ocean_proximity_index'], outputCol='features')

usable_df = vectorAssembler.transform(house_price_df)
usable_df = usable_df.select(['features', 'median_house_value'])

split_data = usable_df.randomSplit([0.7, 3.0], 100)
training_data = split_data[0]
test_data = split_data[1]


model = RandomForest.trainClassifier(training_data, numClasses=2, categoricalFeaturesInfo={}, \
    numTrees=5, maxBins=50,featureSubsetStrategy="auto", maxDepth=5, seed=100)

  
print("\n\nData:\n")
print(model.numTrees())
print(model.totalNumNodes())