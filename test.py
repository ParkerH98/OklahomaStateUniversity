#  Load the TensorBoard notebook extension.
# %load_ext tensorboard
from datetime import datetime
import tensorflow as tf
from tensorflow import keras
import tensorflow.keras.layers as Layer
import tensorboard
import matplotlib.pyplot as plt
import numpy as np
import keras_tuner as kt
import time






np.random.seed(1)
tf.random.set_seed(1)

# columns for DataFrame
movieFields = ['id', 'title', 'vote_average', 'cast', 'cast_ids', 'budget']

# reads csv
movie_dataset = pd.read_csv('formatted_movies.csv', skipinitialspace=True, usecols=movieFields)

# creates DataFrame from movie_dataset
df = pd.DataFrame(movie_dataset)

y_train = df['vote_average']
x_train = df[['id', 'budget', 'cast_ids']]





# # Sequential Model
feed_forward_model = keras.models.Sequential([
    # keras.layers.Flatten(input_shape=(32, 32, 3)),
    keras.layers.Dense(10, activation='relu'),
    keras.layers.Dense(20, activation='relu'),
    keras.layers.Dense(1, activation='relu')
])


# # Sequential Model
feed_forward_model = keras.models.Sequential([
    # keras.layers.Flatten(input_shape=(32, 32, 3)),
    keras.layers.Dense(10, activation='relu'),
    keras.layers.Dense(20, activation='relu'),
    keras.layers.Dense(1, activation='relu')
])