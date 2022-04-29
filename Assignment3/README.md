# BDM-Group8-Assignment3

<hr>

### Authors

- Parker Hague
- Yuhan Jin
- Dax Jones
<hr>

<!-- todo -->

### Contents

- Group_8_Program_1.py
- Group_8_Program_2.py
- Group_8_README_1.txt
- Group_8_README_2.txt
<hr>

<!-- todo -->

### About

The two python files each submit the same query, but while each using different methods to do so.
The file `Group_8_Program_1.py` uses raw SQL as the query method. The second file, `Group_8_Program_2.py`, uses Spark dataframes and their built-in functions as the query method. Both methods will return the same result.

### General Usage Instructions

#### Logging into Hadoop Cluster

    ssh username@hadoop-nn001.cs.okstate.edu

#### Viewing the Dataset

    hdfs dfs -cat /user/kaggle/kaggle_data/california_housing.csv

<!-- todo -->

#### Running the Program

    spark-submit house_avg.py

<!-- todo -->

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

<hr>

## Task 1 - Data Correction

### Preliminary Setup

#### Feature / Target Selection

First, we need to decide which columns or features we are going to keep from the dataset
and which ones we are going to discard. We also need to determine which value we will be predicting (target value).
We decided to use the following columns as features for training our models:

1. `housing_median_age`
2. `total_rooms`
3. `total_bedrooms`
4. `population`
5. `ocean_proximity`

We also decided that our target value would be `median_house_value` because it seemed like the only dependent
variable when considering all of the fields in the dataset.

#### Category Indexing
One of the columns in our dataset, `ocean_proximity`, contained categorical data. Since this data is in a string
format, it cannot be put into the regression model. This makes sense because you can't do math operations on a 
word. We need a number to represent each instead. I used `StringIndexer` which looks at the column values and puts
the unique strings into a dictionary and assigns them a numerical value starting at 0. This way, for example, `NEAR BAY`
can be represented with a 0 and `INLAND` with a 1.


<hr>

### Part A - Define Out of Range

#### Approach 1-A

We need to filter out the outliers in the dataset so we can get a more accurate prediction from our models.
To do this, we need to determine a specific range that is reasonable for each column. We decided to take a
statistical approach when determining the range of values to keep. If we assume our data follows a normal
distribution then we know that 97% of our data should fall between +- 3 standard deviation from the mean.
Using this knowledge, we decided to filter out datapoints that were **4 standard deviations** from the mean as
we consider these to be extreme outliers. In the end, we **filtered out 598 values**. This accounts for **2.89%** of
the dataset. So now that we have determined which values to get rid of, what do we do with them?

Once we select the values that are out of their specified range, we set their value to `null`. There is a very
important reason for this. We set the bad values to `null` because the next part of the pipeline process is a
function that will find each `null` value and replace it when the average of its **k nearest neighbors**.

#### Implementation 1-A

<hr>

### Part B - Replace Missing Values

#### Approach 1-B

We have a number of options when deciding how to handle the missing values. We could just replace their values with
the mean of its column, but that wouldn't give us a value that's correlated to the rest of the other values in the row.
Instead, we can replace the value using some kind of similarity algorithm. We decided to use the **KNN Imputer** from the
sklearn library.

The Imputer works by specifying a `k` value. This value specifies how many of the next closest (or similar) datapoints the
algorithm will use when determining the replacement value. How does it determine which points are similar? It calculates the
**euclidean distance** of the row with the missing value to all of the other rows in the dataset. The vectors with smaller
euclidean distances are more similar. Once we know the `k` most similar rows, we can replace the missing value by getting
the average of the `k` rows with respect to the specific missing value's column. By using the `k` most similar datapoints to
calculate the average, we can get a more accurate approximation of the missing value.

#### Implementation 1-B

<hr>

## Task 2 - Prediction Algorithm

### Part A - Linear Regression

#### Approach 2-A

The first prediction algorithm we used was linear regression. Linear regression is used to predict a **continuous**
value. In our case, our continuous value will be thr target value, `median_house_value`. We will use the five features,
`housing_median_age`, `total_rooms`, `total_bedrooms`, `population`, `ocean_proximity` as inputs into the linear regression
model to make our prediction.

Before inputting them into the model, we first pass out dataframe into a `VectorAssembler`. The `VectorAssembler` takes each
row and column of the dataframe and turns them into row vectors. This list of vectors allows us to have an
input format that the model will accept.

#### Implementation 2-A

<hr>

### Part B - Random Forest

#### Approach 2-B

#### Implementation 2-B

<hr>

## Task 3 - Measure Accuracy

### Part A - RMSE
When making predictions with a model, we have to have a way to measure how well the model is doing. For our models,
we can use RMSE or root mean square error as a metric to calculate the error

#### Approach 3-A

#### Implementation 3-A

<hr>

## Task 4 - Create a Spark Pipeline

### Part A - Pipeline

#### Approach 3-A

#### Implementation 3-A

<hr>



## Task 5 - Principal Component Analysis

### Part A - mat

#### Approach 3-A

#### Implementation 3-A

### Part B - comp

#### Approach 3-A

#### Implementation 3-A

### Part C - acor

#### Approach 3-A

#### Implementation 3-A
