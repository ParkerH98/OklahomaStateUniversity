# BDM-Group8
<hr>

## General Instructions

### Logging into Hadoop Cluster
ssh username@hadoop-nn001.cs.okstate.edu

### Viewing the Dataset
hdfs dfs -cat /user/kaggle/kaggle_data/bucharest_housing_prices/house_offers.csv

### Running the Program
    spark-submit house_avg.py

<hr>

## Bucharest Housing Prices Dataset

### Dataset Fields
id,
location,
location_area,
seller_type,
type,
partitioning,
comfort,
price,
rooms_count,
useful_surface,
built_surface,
construction_year,
real_estate_type,
height_regime,
level,
max_level,
kitchens_count,
bathrooms_count,
garages_count,
parking_lots_count,
balconies_count

### Sample Data
    101,"Bucuresti, Sector 6, zona Drumul Taberei",Drumul Taberei,agency,apartament,decomandat,lux,37400,2,65,65,2018,bloc de apartamente,S+P+6E,2,6,1,1,,1,1
