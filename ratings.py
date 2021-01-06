import numpy as np
import re
import pandas as pd
from sklearn.linear_model import LinearRegression  

movieFields = ['id', 'title', 'vote_average', 'cast']

movieData = pd.read_csv('movies.csv', skipinitialspace=True, usecols=movieFields)

df = pd.DataFrame(movieData)

y = df['vote_average']
x = df[['title', 'cast']]

# define model
