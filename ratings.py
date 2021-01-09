import numpy as np
import re
import pandas as pd
from sklearn.linear_model import LinearRegression
from collections import defaultdict
from format import *
import csv

# columns for DataFrame
movieFields = ['id', 'title', 'vote_average', 'cast']

# reads csv
movie_dataset = pd.read_csv('movies.csv', skipinitialspace=True, usecols=movieFields)

# creates DataFrame from movie_dataset
df = pd.DataFrame(movie_dataset)

# gets unique keys from actors i.e:
# ['Tom Hanks', 'Will Smith', 'Tom Hanks', 'Jonah Hill', 'Tom Hanks', 'Will Smith', 'Jonah Hill']
# returns list [0, 1, 0, 2, 0, 1, 2]
key_assignment = defaultdict(lambda: len(key_assignment))

# list of unique keys for each actor
keys = [key_assignment[key] for key in all_names]

# assigns keys to actors to form a hash table...nums are keys
actor_dict = dict(zip(keys, all_names))

# inverts dictionary...names are keys
actor_dict_inv = {v: k for k, v in actor_dict.items()}


# w = csv.writer(open("actor_dict.csv", "w"))
# for key, val in actor_dict.items():
#     w.writerow([key, val])

print(inv_map.get(0))
# print(fruit_dictionary)
# print(actorDictionary.get(567))

# temp = actorDictionary.keys()

# y = df['vote_average']
# x = df[['title', temp]]

# # define model
# linear_regression = LinearRegression()
# linear_regression.fit(x, y)

# y_pred = linear_regression.predict(x)

# y_pred