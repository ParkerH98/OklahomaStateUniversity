import pandas as pd
import numpy as np
import random as rd
from pyspark.sql import SparkSession
from sklearn.decomposition import PCA
from sklearn import preprocessing
from pyspark import SparkConf, SparkContext
import sys
from pyspark.sql import SQLContext
from pyspark.sql.types import StringType, FloatType, StructType
from pyspark.ml.feature import OneHotEncoder, StringIndexer, VectorAssembler
from pyspark.ml import Pipeline
from pyspark.ml.linalg import Vectors
import pyspark.sql.functions as f
from functools import reduce
from pyspark.sql.functions import udf
import numpy as np
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt

# Provide a print format
def format_print(PCA_output):
	print(80 * '*')
	print(PCA_output)
	print(80 * '*')
	return



format_print('Configuration')

# doing the spark configuration
conf = SparkConf().setMaster("yarn").setAppName("Part_5_A3")
# hide info lines
part_five_spark_csv = SparkContext(conf=conf)
part_five_spark_csv.setLogLevel("WARN")
part_five_spark_csv_sql = SQLContext(part_five_spark_csv)
pd.options.display.max_columns = None


spark = SparkSession.builder.getOrCreate()

format_print('Read csv file')

# request the file location
# command_line_arg = sys.argv[1]
# command_line_arg_type = command_line_arg.split('.')[-1] 
#  # warning for no csv file
# if command_line_arg_type != 'csv':  
#     raise ValueError('need csv file input.')

get_index_one="true"
get_index_two="true"
get_index_three=","

# use SQLContext to load the file
# input_data_frame = part_five_spark_csv_sql.read.format(command_line_arg_type)\
# 	.option("inferSchema",get_index_one)\
# 	.option("header",get_index_two)\
# 	.option("sep",get_index_three)\
# 	.load(command_line_arg)
 
# reads dataset from file in HDFS to a spark dataframe
input_data_frame = spark\
	.read\
	.option("inferSchema", "true")\
	.option("header", "true")\
	.csv("hdfs:///user/kaggle/kaggle_data/california_housing.csv")


format_print('data set Analysis')


# print rows num 
part_five_row_num = input_data_frame.count()
print('The number of rows in the dataset: {}'.format(part_five_row_num))
# print cols num 
part_five_col_num = len(input_data_frame.columns)
print('The number of columns in the dataframe: {}'.format(part_five_col_num))
# get the current description 
input_data_frame.printSchema()

# make these cols into lists
longitude_list = list(input_data_frame.select('longitude').toPandas()['longitude'])
latitude_list = list(input_data_frame.select('latitude').toPandas()['latitude'])
housing_median_age_list = list(input_data_frame.select('housing_median_age').toPandas()['housing_median_age'])
total_rooms_list = list(input_data_frame.select('total_rooms').toPandas()['total_rooms'])
population_list = list(input_data_frame.select('population').toPandas()['population'])
households_list = list(input_data_frame.select('households').toPandas()['households'])
median_income_list = list(input_data_frame.select('median_income').toPandas()['median_income'])
median_house_value_list = list(input_data_frame.select('median_house_value').toPandas()['median_house_value'])
  
# create a array with id num equal to row num
id_num = ['id' + str(num) for num in range(1,part_five_row_num+1)]
# create arraies of col names
longitude = ['longitude']
latitude = ['latitude']
housing_median_age = ['housing_median_age']
total_rooms = ['total_rooms']
population = ['population']
households = ['households']
median_income = ['median_income']
median_house_value = ['median_house_value']
# create a pandas df to store our newly created df
data_frame_two = pd.DataFrame(columns=[*longitude, *latitude, *housing_median_age, *total_rooms, *population, *households, *median_income, *median_house_value], index=id_num)
num=0
# assign the values 
while(num < part_five_row_num):

	for id_num[num] in data_frame_two.index:
		data_frame_two.loc[id_num[num],'longitude'] =longitude_list[num]
		data_frame_two.loc[id_num[num],'latitude'] = latitude_list[num]
		data_frame_two.loc[id_num[num],'housing_median_age'] = housing_median_age_list[num]
		data_frame_two.loc[id_num[num],'total_rooms'] =total_rooms_list[num]
		data_frame_two.loc[id_num[num],'population'] = population_list[num]
		data_frame_two.loc[id_num[num],'households'] = households_list[num]
		data_frame_two.loc[id_num[num],'median_income'] =median_income_list[num]
		data_frame_two.loc[id_num[num],'median_house_value'] = median_house_value_list[num]
		
		num+=1
	
# check the first 5 row 
print(data_frame_two.head())
print(data_frame_two.shape)
 

# set up the standardized data 
data_frame_three = StandardScaler().fit_transform(data_frame_two)
  


# initialize our pca
pca = PCA(n_components=8)
data_frame_four = pca.fit_transform(data_frame_three)
# get the Main component score\
format_print('Eigenvector')
print (pca.components_)
format_print('Contribution rate')
print (pca.explained_variance_)
format_print('Main component score')
print(data_frame_four)
