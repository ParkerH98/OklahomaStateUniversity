
## About

This program takes a movie genre and up to five actors as an input. It then will predict a movie rating for the
input on a scale of 0 - 10.

#### Example Inputs


| Input | Actual Rating | FFNN Predicted | RNN Predicted | Naïve Bayes Predicted | Movie |
|---|---|---|---|---|---|
| 'Drama DannyGlover RonPerlman LindaHamilton ZoeWeizenbaum DavidStrathairn' | 6.10 | 6.188 | 6.521 | 6 | Missing in America |
| 'Drama PaulWalker PiperPerabo LambertWilson LindaCardellini ShawnHatosy' | 6.0 | 6.464 | 7.356 | 6 | The Lazarus Project |
| 'Comedy MollyShannon WillFerrell ElaineHendrix HarlandWilliams TomGreen' | 5.0 | 5.695 | 5.130 | 5 | Superstar |

### Usage

Run the main file, `MovieRatings.ipynb`, as normal. Make sure the following files are
accompanied with it in the root directory:
- `DatasetFormatting.py`
- `datafiles`
  - `movies_metadata.csv`
  - `credits.csv`

We have a whole python file that handles all the data formatting. The actual model training and implementation is done in the
MovieRatings notebook. To run the three models, simply just run the entire notebook file. We have included various tests for each 
model including tests in the training set and tests in the test set.

The program doesn't have any bugs and should run perfectly on the first try. If it doesn't, then please contact Parker Hague, Dax Jones, 
or Steven Mikels.

### Dependencies:

- Tensorboard
- Matplotlib
- Numpy
- Tensorflow
- Pandas
- Scikit-Learn
