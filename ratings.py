import numpy as np
import re
import pandas as pd
from sklearn.linear_model import LinearRegression  

movieFields = ['id', 'title', 'vote_average']
castFields = ['id', 'cast']

movieData = pd.read_csv('../archive/movies_metadata.csv', skipinitialspace=True, usecols=movieFields)
castData = pd.read_csv('../archive/credits.csv', skipinitialspace=True, usecols=castFields)

dfMovies = pd.DataFrame(movieData)
dfMovies['title'] = dfMovies['title'].astype(str)
dfMovies['id'] = dfMovies['id'].astype(int)

dfCast = pd.DataFrame(castData)
dfCast['cast'] = dfCast['cast'].astype(str)
dfCast['id'] = dfCast['id'].astype(int)

df = pd.merge(dfMovies, dfCast, how='inner')

names = df['cast']

actors = []

for row in names:

    line = [re.findall("(?<=\'name\': )(.*?)(?=,)", row)]
    actors.append(line)


df['cast'] = actors

print(df)