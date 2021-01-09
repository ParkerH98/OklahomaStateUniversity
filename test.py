import numpy as np
import re
import pandas as pd
from sklearn.linear_model import LinearRegression
from collections import defaultdict 





namesTest = ['test', 'tester', 'test', 'bigtest', 'test', 'tester', 'bigtest']

testDF = pd.DataFrame(namesTest)

print(testDF)

tempp = pd.factorize(namesTest)

keys = pd.factorize(namesTest)[0]
names = pd.factorize(namesTest)[1]

temp = defaultdict(lambda: len(temp)) 
res = [temp[ele] for ele in namesTest]

w = csv.writer(open("actor_dictionary.csv", "w"))
for key, val in dict.items():
    w.writerow([key, val])

print(str(res))


fruit_dictionary = dict(zip(res, namesTest))

print(fruit_dictionary)

print(fruit_dictionary.get(0))

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

# y = df['vote_average']
# x = df[['title', 'cast']]

# # define model
# linear_regression = LinearRegression()
# linear_regression.fit(x, y)

# y_pred = linear_regression.predict(x)

# y_pred