# Movie Ratings ML Project

## Table of Contents
- [Movie Ratings ML Project](#movie-ratings-ml-project)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Example Inputs](#example-inputs)
  - [Dataset](#dataset)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Usage](#usage)
  - [Model Descriptions](#model-descriptions)
  - [Results](#results)
  - [Contact](#contact)

## Overview
The Movie Ratings Predictor is a program that accepts a movie genre and up to five actors as input. It then predicts a movie rating for the given inputs on a scale of 0 - 10. The prediction process is done by employing three different machine learning models: FFNN (Feed Forward Neural Network), RNN (Recurrent Neural Network), and Naïve Bayes.

## Example Inputs
Here are some sample inputs and corresponding predictions from each of the models.

| Input | Actual Rating | FFNN Predicted | RNN Predicted | Naïve Bayes Predicted | Movie |
|---|---|---|---|---|---|
| 'Drama DannyGlover RonPerlman LindaHamilton ZoeWeizenbaum DavidStrathairn' | 6.10 | 6.188 | 6.521 | 6 | Missing in America |
| 'Drama PaulWalker PiperPerabo LambertWilson LindaCardellini ShawnHatosy' | 6.0 | 6.464 | 7.356 | 6 | The Lazarus Project |
| 'Comedy MollyShannon WillFerrell ElaineHendrix HarlandWilliams TomGreen' | 5.0 | 5.695 | 5.130 | 5 | Superstar |

## Dataset
The project uses two datasets: `movies_metadata.csv` and `credits.csv`, which are part of the Movies Dataset available on Kaggle. You can access the datasets [here](https://www.kaggle.com/datasets/rounakbanik/the-movies-dataset).

## Getting Started

### Prerequisites
Before running the program, please make sure you have the following Python libraries installed:

- TensorFlow: Used to create and train the neural network models.
- sklearn: Specifically, the train_test_split function for splitting the dataset, and the CategoricalNB function for the Naive Bayes model.
- NumPy: For various numerical operations.
- pandas: For handling the dataset.
- Matplotlib: For visualizing data and results.
- Statistics: For calculating descriptive statistics.
- TensorBoard: For visualizing the model training process.

### Usage
1. Ensure that the main file `MovieRatings.ipynb` is placed in the root directory along with `DatasetFormatting.py` file and `datafiles` directory.
2. The `datafiles` directory should include the following files:
   - `movies_metadata.csv`
   - `credits.csv`
3. Execute the `MovieRatings.ipynb` notebook file. All data formatting, model training, and implementation will be done in this file.
4. Simply run the entire notebook file to execute the three models. Tests for each model are included for both the training set and test set.

The program is expected to run without issues on the first try. In case of any difficulties, please reach out to the contacts listed below.

## Model Descriptions
This project employs three different machine learning models for movie rating prediction. Each model increases in complexity, starting with a simple baseline and ending with a more sophisticated approach. Here are brief descriptions of each model:

- **Feed Forward Neural Network (FFNN)**: The FFNN is an artificial neural network where information travels in one direction, from the input nodes through the hidden nodes (if any) and finally to the output node. We selected the FFNN as our baseline model due to its simplicity. In this model, the movie genre and actors serve as input data, which the FFNN processes to predict a rating.

- **Recurrent Neural Network (RNN)**: An advancement over the FFNN, the RNN has connections that form directed cycles. This architecture creates a form of internal state memory, allowing the RNN to capture temporal patterns. We leverage this feature to consider the sequence of actors and genre, which provides a more nuanced prediction of movie ratings.

- **Naïve Bayes**: The Naïve Bayes model differs from the FFNN and RNN in that it's a classification technique, not a prediction of a continuous value. It's based on applying Bayes' theorem with the "naive" assumption of independence between every pair of features. This model is highly scalable and offers a simple yet effective method for predicting movie ratings based on the genre and actors. We chose to use Naïve Bayes for its simplicity and the contrasting approach it offers compared to the other models.

## Results
*[Summary of the results or findings goes here]*

## Contact
For further queries or troubleshooting, please contact:
- Parker Hague
- Dax Jones
- Steven Mikels