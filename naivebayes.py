import pandas as pd
import numpy as np
import DatasetFormatting as df

def roundY(y_col):
  print()


def naiveBayes(X, y):
 from sklearn.model_selection import train_test_split
 import sklearn.naive_bayes as NB


 x_train, x_test, y_train, y_test = train_test_split(X, y, test_size=0.25)
 NBmodel = NB.CategoricalNB()
 NBmodel = NBmodel.fit(x_train, y_train)
 return NBmodel


def prepareForNB(data):
  all_actors = data['cast'].to_list()
  genres = data['genres'].to_list()

  X = []
  for i in range(0, len(all_actors)):
    row = all_actors[i].split()
    row.insert(0, genres[i])
    if len(row) < 6:
      for i in range(0, 6 - len(row)):
        row.append('')

    X.append(row)
  
  genres = data['genres'].to_list()

  ratings = data['vote_average'].to_list()
  for i in range(0, len(ratings)):
    ratings[i] = round(ratings[i])

  return X, ratings

def main():
  data = df.getData()
  X, ratings = prepareForNB(data)
  print(X[0])
  # NBmodel = naiveBayes(X, ratings)
  


if __name__ == "__main__":
  main()

