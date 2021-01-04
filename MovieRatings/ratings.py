import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression




movieFields = ['id', 'title', 'vote_average']
castFields = ['id', 'cast']


movieData = pd.read_csv('archive/movies_metadata.csv', skipinitialspace=True, usecols=movieFields)

castData = pd.read_csv('archive/credits.csv', skipinitialspace=True, usecols=castFields)

# df = df[df.employee_name != 'chad']
dfMovies = pd.DataFrame(movieData)
dfMovies = dfMovies[dfMovies['title'] != 'Nan'] 
dfCast = pd.DataFrame(castData)

df = pd.merge(dfMovies, dfCast, how='inner')

# cast = dfTemp['cast']


# print(df.sort_values(by='id'))