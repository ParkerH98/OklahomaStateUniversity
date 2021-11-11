import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
import sklearn.naive_bayes as NB
import DatasetFormatting as df
import matplotlib.pyplot as plot

def roundY(y_col):
  print()


def naiveBayes(X, y):
 NBmodel = NB.CategoricalNB()
 NBmodel = NBmodel.fit(X, y)
 return NBmodel


def prepareForNB(data):
  all_actors = data['cast'].to_list()
  genres = data['genres'].to_list()

  X = []
  unique_keys = {'': 0}
  unique_key = 1

  for i in range(0, len(all_actors)):
    row = []

    raw_row = all_actors[i].split()
    raw_row.insert(0, genres[i])
    if len(raw_row) < 6:
      for i in range(0, 6 - len(raw_row)):
        raw_row.append('')

    for item in raw_row:
      if item not in unique_keys:
        unique_keys[item] = unique_key
        unique_key += 1
      row.append(unique_keys[item])

    X.append(row)
  
  genres = data['genres'].to_list()

  ratings = data['vote_average'].to_list()
  for i in range(0, len(ratings)):
    ratings[i] = round(ratings[i])

  return X, ratings

def main():
  data = df.getData()
  X, ratings = prepareForNB(data)

  data_count = data.shape[0]
  training_data_count = int(data_count * 0.75) + 1
  test_data_count = data_count - training_data_count

  y_train = np.array(ratings[0:training_data_count])
  x_train = np.array(X[0:training_data_count])

  y_test = np.array(ratings[:-1 * test_data_count])
  x_test = np.array(X[:-1 * test_data_count])

  NBmodel = naiveBayes(x_train, y_train)

  y_pred = NBmodel.predict(x_test)
  
  total_correct = 0
  for i in range(0, y_test.shape[0]):
    if int(y_pred[i]) == y_test[i]:
      total_correct += 1
  
  
  accuracy = total_correct/y_test.shape[0]
  print(f"Total Correct Ratio: {total_correct}/{y_test.shape[0]}")
  print(accuracy)

  plot.figure(figsize = [10, 10])
  actuals = plot.scatter(np.linspace(0, y_test.shape[0], y_test.shape[0]), y_test, color='red', marker='.')
  estimates = plot.scatter(np.linspace(0, y_test.shape[0], y_test.shape[0]), y_pred, color='blue', marker='.')
  plot.legend([actuals, estimates], ["Actuals", "Estimated"])
  plot.show()
  


if __name__ == "__main__":
  main()

