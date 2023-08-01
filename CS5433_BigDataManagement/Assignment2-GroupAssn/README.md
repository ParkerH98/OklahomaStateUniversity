# BDM-Group8
<hr>

### Authors
- Parker Hague
- Yuhan Jin
- Dax Jones
<hr>

### Contents
- Group_8_Program_1.py
- Group_8_Program_2.py
- Group_8_README_1.txt
- Group_8_README_2.txt
<hr>

### About
The two python files each submit the same query, but while each using different methods to do so.
The file ```Group_8_Program_1.py``` uses raw SQL as the query method. The second file, ```Group_8_Program_2.py```, uses Spark dataframes and their built-in functions as the query method. Both methods will return the same result.

### General Usage Instructions

#### Logging into Hadoop Cluster
    ssh username@hadoop-nn001.cs.okstate.edu

#### Viewing the Dataset
    hdfs dfs -cat /user/kaggle/kaggle_data/california_housing.csv

#### Running the Program
    spark-submit house_avg.py

#### Expected Output

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
<hr>

## California Housing Prices Dataset

#### Dataset Fields
longitude,
latitude,
housing_median_age,
total_rooms,
total_bedrooms,
population,
households,
median_income,
median_house_value,
ocean_proximity

#### Sample Data
    -122.23,37.88,41.0,880.0,129.0,322.0,126.0,8.3252,452600.0,NEAR BAY
