from pyspark.ml.regression import RandomForestRegressor
from pyspark.ml.regression import LinearRegression
from pyspark.sql import SparkSession
from pyspark.ml.feature import VectorAssembler
from pyspark.ml.feature import StringIndexer
from pyspark.ml.evaluation import RegressionEvaluator

from pyspark.ml import Pipeline

spark = SparkSession.builder.getOrCreate()
spark.sparkContext.setLogLevel('WARN')

    
# reads dataset from file in HDFS to a spark dataframe
house_price_df = spark\
    .read\
    .option("inferSchema", "true")\
    .option("header", "true")\
    .csv("hdfs:///user/kaggle/kaggle_data/california_housing.csv")

indexer = StringIndexer(inputCol="ocean_proximity",
                        outputCol="ocean_proximity_index")
# house_price_df = indexer.fit(house_price_df).transform(house_price_df)

# Split data into training/testing
split_data = house_price_df.randomSplit([.75, .25], 100)
training_data = split_data[0]
test_data = split_data[1]


# Build vector assembler
vectorAssembler = VectorAssembler(inputCols=['longitude', 'latitude', 'housing_median_age', 'total_rooms', 'total_bedrooms',
                                  'population', 'households', 'median_income', 'ocean_proximity_index'], outputCol='features')

# usable_df = vectorAssembler.transform(house_price_df)                 May be used later but pipeline should do it
# usable_df = usable_df.select(['features', 'median_house_value'])


# Build Model
lr_model = LinearRegression(featuresCol='features', labelCol='median_house_value')
rf_model = RandomForestRegressor(featuresCol="features", labelCol='median_house_value', predictionCol="predictions", maxBins=50, seed=100)


# Build Evaluator
evaluator = RegressionEvaluator(labelCol="median_house_value",
                                predictionCol="predictions",
                                metricName="rmse")

# Create pipelines
lr_pipeline = Pipeline(stages=[indexer, vectorAssembler, lr_model, evaluator])
rf_pipeline = Pipeline(stages=[indexer, vectorAssembler, rf_model, evaluator])

lr_pipeline_model = lr_pipeline.fit(training_data)
rf_pipeline_model = rf_pipeline.fit(training_data)

lr_results = lr_pipeline_model.transform(test_data)
rf_results = lr_pipeline_model.transform(test_data)

lr_results.show()
rf_results.show()



