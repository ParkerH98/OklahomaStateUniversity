import sys
import pyspark.sql.functions as f
import numpy as np
from pyspark import SparkConf, SparkContext
from pyspark.sql import SQLContext, SparkSession
from pyspark.sql.types import StringType, FloatType, StructType
from pyspark.ml.feature import OneHotEncoder, StringIndexer, VectorAssembler
from pyspark.ml import Pipeline
from pyspark.ml.linalg import Vectors
from functools import reduce
from pyspark.sql.functions import udf
from pyspark.sql.functions import col





conf = SparkConf().setMaster("yarn").setAppName("Group8_P1")
Spark_csv_configuration = SparkContext(conf=conf)
Spark_csv_configuration.setLogLevel("WARN")
Spark_csv_configuration_sql = SQLContext(Spark_csv_configuration)
print('Read csv file')


get_file_location = sys.argv[1]
get_file_csv = get_file_location.split('.')[-1]  


part_one_schema="true"
Part_one_header="true"
Part_one_split=","

Part_one_data_frame = Spark_csv_configuration_sql.read.format(get_file_csv)\
	.option("inferSchema",part_one_schema)\
	.option("header",Part_one_header)\
	.option("sep",Part_one_split)\
	.load(get_file_location)

part_one_r = Part_one_data_frame.count()

part_one_c = len(Part_one_data_frame.columns)

Part_one_data_frame.printSchema()

col_contains_string = ['ocean_proximity']

for num in range(len(col_contains_string)):
	col_contains_strings = col_contains_string[num]
	Part_one_data_frame_one = Part_one_data_frame.select(col_contains_strings)
	Part_one_data_frame_two = Part_one_data_frame_one.distinct()
	Part_one_data_frame_two.toPandas().to_csv('{}.csv'.format(col_contains_string[num]))

Part_one_data_frame_one = Part_one_data_frame.select('ocean_proximity', 'median_house_value')
Part_one_data_frame_two = Part_one_data_frame_one.distinct()
Part_one_data_frame_two.toPandas().to_csv('ocean_proximity-median_house_value_count.csv')


num_one = [StringIndexer(inputCol=c, outputCol='{0}_indexed'.\
			  format(c)) for c in col_contains_string]

pipeline = Pipeline(stages=num_one)
Part_one_data_frame_two = pipeline.fit(Part_one_data_frame).transform(Part_one_data_frame)
Part_one_data_frame_two.toPandas().to_csv('strings_indexed.csv')

Part_one_data_frame_c = Part_one_data_frame_two.schema.names
Part_one_data_frame_c = [Part_one_data_frame_c[num] for num in range(len(Part_one_data_frame_c)) if Part_one_data_frame_c[num] not in col_contains_string]
Part_one_data_frame_three = Part_one_data_frame_two.select(*Part_one_data_frame_c)
Part_one_data_frame_three.toPandas().to_csv('strings_indexed_reduced.csv')

for c_n in Part_one_data_frame_c:
	Part_one_data_frame_three = Part_one_data_frame_three.withColumn(c_n, col(c_n).cast('float'))

Part_one_data_frame_three.printSchema()
print('dataframe that contain out of range values')



null_col = Part_one_data_frame_three.where(reduce(lambda i, j: i | j, (f.col(i).isNull() \
                           for i in Part_one_data_frame_three.columns)))
print('The number of rows containing null values: {}'.\
       format(null_col.count()))
out_of_range = Part_one_data_frame_three.where(reduce(lambda i, j: i | j, (f.col(i) < 800 \
                            for i in Part_one_data_frame_three.columns)))
print('The number of rows containing < 800: {}'.\
      format(out_of_range.count()))
Part_one_data_frame_x = null_col.unionAll(out_of_range)
print('The mal-dataframe')
Part_one_data_frame_x.show()
n_rows_mal = Part_one_data_frame_x.count()
print('Total number of mal rows: {}'.format(n_rows_mal))

not_null_col = Part_one_data_frame_three.dropna()

Part_one_data_frame_y = not_null_col.exceptAll(out_of_range)

n_rows_gut = Part_one_data_frame_y.count()
print('Good dataframe count: {}'.format(n_rows_gut))

total_rows = n_rows_mal + n_rows_gut
print('The total rows in the good and bad dataframes are: {}'.\
						    format(total_rows))
print('Define functions for normalizing a dataframe')

def part_one_norm(Part_one_data_frame, part_one_mean, s_d, num_x):
	Part_one_data_frame = Part_one_data_frame.withColumn(num_x + '_norm', \
                          ((Part_one_data_frame[num_x] - part_one_mean[num_x]) \
                            / s_d[num_x + '_stddev']))
	return Part_one_data_frame


def part_one_norm_a(Part_one_data_frame, num_y):

	aggExpr = []
	aggStd = []
	for num_x in num_y:
		aggExpr.append(f.mean(Part_one_data_frame[num_x]).alias(num_x))
		aggStd.append(f.stddev(Part_one_data_frame[num_x]).\
			      alias(num_x + '_stddev'))

	part_one_mean = Part_one_data_frame.agg(*aggExpr).collect()[0]
	s_d = Part_one_data_frame.agg(*aggStd).collect()[0]
	return part_one_mean, s_d

def part_one_norm_b(Part_one_data_frame, num_y, part_one_mean, s_d):

	for num_x in num_y:
		Part_one_data_frame = part_one_norm(Part_one_data_frame, part_one_mean, s_d, num_x)
	return Part_one_data_frame


def part_one_norm_c(train_df, test_df, num_y):

	part_one_mean, s_d = part_one_norm_a(train_df, num_y)

	train_df = part_one_norm_b(train_df, 
					     num_y, 
				   	     part_one_mean, 
					     s_d)
	test_df = part_one_norm_b(test_df, 
					    num_y, 
					    part_one_mean, 
					    s_d)

	return train_df, test_df, part_one_mean, s_d

print('Define useful re-usable functions for accessing dataframes')


def get_index(Part_one_data_frame, c_n='id'):

	return Part_one_data_frame.withColumn(c_n, f.monotonically_increasing_id())


def part_one_vector(Part_one_data_frame, inputCols, outputCol='Vector'):

	if outputCol in Part_one_data_frame.columns:
		Part_one_data_frame = Part_one_data_frame.drop(outputCol)

	vecAssembler = VectorAssembler(inputCols=inputCols, 
			               outputCol=outputCol, 
			               handleInvalid='keep')
	Part_one_data_frame = vecAssembler.transform(Part_one_data_frame)
	return Part_one_data_frame


def get_id(Part_one_data_frame, id_num, c_n='Vector'):
	
	return Part_one_data_frame.filter(col('id') == id_num).select(c_n).head()[0]


def r_limit(Part_one_data_frame, colName='coSim'):

	maxVal = Part_one_data_frame.agg(f.max(colName)).collect()[0][0]
	row = Part_one_data_frame.filter(f.col(colName) == maxVal).first()
	return row, maxVal
print('Define functions for computing cosine similarity')

def cos_s(a, b):
        return float(np.dot(a, b) / \
                              (np.linalg.norm(a) * np.linalg.norm(b)))

def c_s(Part_one_data_frame, single_vector, inputCol='Vector', 
			      outputCol='coSim'):
	
	if outputCol in Part_one_data_frame.num_y:
		Part_one_data_frame = Part_one_data_frame.drop(outputCol)

	Part_one_data_frame = Part_one_data_frame.withColumn('coSim', udf(cos_s, FloatType())\
			   (f.col('Vector'), f.array([f.lit(v) \
                                             for v in single_vector])))
	return Part_one_data_frame
print('Use cosine similarity to replace bad values in mal dataframes')


dframe = get_index(Part_one_data_frame_y, c_n='id')
Part_one_data_frame_x = get_index(Part_one_data_frame_x, c_n='id')

Part_one_data_frame_x.show()

col_names = Part_one_data_frame_y.schema.names

col_names = [col_names[num] for num in range(len(col_names)) \
	     if col_names[num] != 'id']
print(col_names)

part_one_mean, s_d = part_one_norm_a(dframe, 
						      col_names)

def f_s(row, col_names):
	col_update_required = None
	bad_val = None
	part_one_get_id = row['id']
	for j in range(len(col_names)):
		a = row[col_names[j]]
		T_a = type(a)
		if T_a is float:
			if a < 0:
				col_update_required = col_names[j]
				bad_val = a
		elif T_a is type(None):
			col_update_required = col_names[j]
			bad_val = a
	return col_update_required, bad_val, part_one_get_id

bad_columns = []
indices = []
mal_vals = []

for row in Part_one_data_frame_x.rdd.collect():
	col_update_required, mal_val, part_one_get_id = f_s(row, col_names)
	if type(col_update_required) is type(None):
		pass
	else:
		bad_columns.append(col_update_required)
		indices.append(part_one_get_id)
		mal_vals.append(mal_val)

print(list(zip(indices, bad_columns)))

def f_r(df_gut, df_mal, mal_col, part_one_get_id, mal_val, part_one_mean, s_d):
	
	c_x = [col_names[num] for num in range(len(col_names)) if col_names[num] != col_update_required]
	

	df_gut = part_one_norm_b(df_gut, c_x, 
                                    part_one_mean, s_d)

	df_mal = part_one_norm_b(df_mal, c_x,
					     part_one_mean, s_d)

	p_v = [c_x[num] + '_norm' \
                     for num in range(len(c_x))]
	df_gut = part_one_vector(df_gut, p_v)

	df_mal = part_one_vector(df_mal, p_v)

	frame_one = get_id(df_mal, part_one_get_id, c_n='Vector')

	df_gut = c_s(df_gut, frame_one)

	row, max_coSim = r_limit(df_gut, colName='coSim')
	part_one_get_id_x = row['id']

	new_value = get_id(df_gut, part_one_get_id_x, c_n=col_update_required)	
	return new_value, part_one_get_id_x
	



col_update_required = bad_columns[0]
part_one_get_id = indices[0]
mal_val = mal_vals[0]
print(mal_vals)
