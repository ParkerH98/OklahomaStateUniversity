from matplotlib.transforms import Transform
from pyspark.ml import Transformer
from pyspark.sql import DataFrame
from sklearn.impute import KNNImputer
import pandas as pd
from pyspark.sql.functions import col, isnan, when, count


class DataDoctorer(Transformer):
    
    def __init__(self, spark):
        super(DataDoctorer, self).__init__()
        self.spark = spark
        

    def _transform(self, df: DataFrame) -> DataFrame:
        df = self.rm_out_of_range_all(df)
        df = self.remove_NULL_values(df) 
        return df

    
    
    def df_spark_to_pandas(self, spark_df):
      pandas_df = spark_df.select("*").toPandas()
      return pandas_df




    def apply_knn_imputer(self, pandas_df):
        imputer = KNNImputer(n_neighbors=10)
        knn_imputed_matrix = imputer.fit_transform(pandas_df)
        corrected_df = pd.DataFrame(knn_imputed_matrix, columns=[
            "housing_median_age",
            "total_rooms",
            "total_bedrooms",
            "population",
            "median_house_value",
            "ocean_proximity_index"])
        return corrected_df






    def remove_NULL_values(self, house_price_df):
        pandas_df = self.df_spark_to_pandas(house_price_df)
        pandas_df = self.apply_knn_imputer(pandas_df)
        house_price_df = self.spark.createDataFrame(pandas_df)

        return house_price_df






    def rm_oor_operations(self, house_price_df, col_to_correct, lower_bound, upper_bound):
        sdf = self.df_spark_to_pandas(house_price_df)

        out_of_range = house_price_df.filter(
            ~col(col_to_correct).between(lower_bound, sdf[col_to_correct].mean() + upper_bound))

        house_price_df = house_price_df.withColumn(col_to_correct, when(
            ~col(col_to_correct).between(lower_bound, sdf[col_to_correct].mean() + upper_bound), None).otherwise(col(col_to_correct)))
        return house_price_df






    def rm_out_of_range_all(self, house_price_df):
        sdf = self.df_spark_to_pandas(house_price_df)

        house_price_df = self.rm_oor_operations(
            house_price_df, "housing_median_age", 0, 2 * sdf['housing_median_age'].std())
        house_price_df = self.rm_oor_operations(
            house_price_df, "total_rooms", 0, 4 * sdf['total_rooms'].std())
        house_price_df = self.rm_oor_operations(
            house_price_df, "total_bedrooms", 0, 4 * sdf['total_bedrooms'].std())
        house_price_df = self.rm_oor_operations(
            house_price_df, "population", 0, 4 * sdf['population'].std())
        return house_price_df
