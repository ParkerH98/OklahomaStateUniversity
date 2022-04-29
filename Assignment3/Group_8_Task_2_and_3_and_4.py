from pyspark.ml.regression import RandomForestRegressor
from pyspark.ml.regression import LinearRegression
from pyspark.sql import SparkSession
from pyspark.ml.feature import VectorAssembler
from pyspark.ml.feature import StringIndexer
from pyspark.ml.feature import OneHotEncoder
from pyspark.ml.evaluation import RegressionEvaluator
from pyspark.ml import Pipeline
import pandas as pd
from sklearn.impute import KNNImputer
from pyspark.sql.functions import col, isnan, when, count
from Group_8_Task_1 import DataDoctorer


def main():
    spark = SparkSession.builder.getOrCreate()
    spark.sparkContext.setLogLevel('OFF')

    print("\n\n\n\n\nStarting process.\n")
        
    # reads dataset from file in HDFS to a spark dataframe
    house_price_df = spark\
        .read\
        .option("inferSchema", "true")\
        .option("header", "true")\
        .csv("hdfs:///user/kaggle/kaggle_data/california_housing.csv")

    
    # removes undesired features
    cols_to_remove = ("longitude", "latitude", "households", "median_income")
    house_price_df = house_price_df.drop(*cols_to_remove)


    # Sets up and indexes strings
    indexer = StringIndexer(inputCol="ocean_proximity",
                            outputCol="ocean_proximity_index")
    house_price_df = indexer.fit(house_price_df).transform(house_price_df)
    house_price_df = house_price_df.drop("ocean_proximity")




    # Split data into training/testing
    split_data = house_price_df.randomSplit([.75, .25], 100)
    training_data = split_data[0]
    test_data = split_data[1]

    # Set Custom Data manipulation for pipeline
    data_doctorer = DataDoctorer(spark)   

    # Build vector assembler
    vectorAssembler = VectorAssembler(inputCols=['housing_median_age', 'total_rooms', 'total_bedrooms',
                                    'population', 'ocean_proximity_index'], outputCol='features')


    # Build Models for part 2a and 2b
    lr_model = LinearRegression(featuresCol='features', labelCol='median_house_value', predictionCol="predictions")
    rf_model = RandomForestRegressor(featuresCol="features", labelCol='median_house_value', predictionCol="predictions", maxBins=50, seed=100)


    # Build Evaluator
    evaluator = RegressionEvaluator(labelCol="median_house_value",
                                    predictionCol="predictions",
                                    metricName="rmse")

    # Create pipelines
    lr_pipeline = Pipeline(stages=[data_doctorer, vectorAssembler, lr_model])
    rf_pipeline = Pipeline(stages=[data_doctorer, vectorAssembler, rf_model])
    
    print(">Fitting models to training data through pipelines.\n")

    # Fit the models based on training
    lr_pipeline_model = lr_pipeline.fit(training_data)
    rf_pipeline_model = rf_pipeline.fit(training_data)


    print(">Making predictions on test data.\n")
    # Make predictions on test data
    lr_results = lr_pipeline_model.transform(test_data)
    rf_results = rf_pipeline_model.transform(test_data)

    print("Results of Linear Regression Predictions(10 rows)\n")
    lr_results.show(10)
    print("\nResults of Linear Regression(10 rows)\n")
    rf_results.show(10)
    print("\n\nRMSE results for Linear Regression: ", evaluator.evaluate(lr_results)) # prints evaluations from RMSE
    print("\nRMSE results for Random Forrest: ", evaluator.evaluate(rf_results))


if __name__ == "__main__":
    main()
