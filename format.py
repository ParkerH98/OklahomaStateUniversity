# I had to split the formatting of the csv between two separate functions.
# Particularly, I had to do this because I needed to apply two different
# regex functions. I was also having problems with the strings storing
# into the list properly after the first regex function.
# There may be a better/more efficient way, but I'm still inexperienced with
# python and pandas.

import re
import pandas as pd

# This function reads in the csv file and extracts all of the names
# from the paragraph of cast information given in credits.csv.
# After, the names will appear in the format: ['Mark Hamill', 'Harrison Ford']
def format1():

    movieFields = ['id', 'title', 'vote_average']
    castFields = ['id', 'cast']

    movieData = pd.read_csv('../archive/movies_metadata.csv', skipinitialspace=True, usecols=movieFields)
    castData = pd.read_csv('../archive/credits.csv', skipinitialspace=True, usecols=castFields)

    dfMovies = pd.DataFrame(movieData)
    dfCast = pd.DataFrame(castData)

    df = pd.merge(dfMovies, dfCast, how='inner')

    unformattedNames = df['cast']

    partiallyFormatted = []

    for row in unformattedNames:

        line = re.findall("(?<=\'name\': )(.*?)(?=,)", row)
        partiallyFormatted.append(line)
    
    df['cast'] = partiallyFormatted

    print(df)

    pd.DataFrame.to_csv(df, "format-temp.csv", index="false")


# This function is needed to further extract the cast names from
# the csv. After this function executes, the names will appear
# in the format: [Mark Hamill, Harrison Ford]
def format2():
    movieFields = ['id', 'title', 'vote_average', 'cast']

    movieData = pd.read_csv('format-temp.csv', skipinitialspace=True, usecols=movieFields)

    df = pd.DataFrame(movieData)

    unformattedNames = df['cast']

    formattedActors = []

    for row in unformattedNames:

        line = re.findall("(?<=\"\')(.*?)(?=\'\")", row)

        formattedActors.append(line)

    df['cast'] = formattedActors

    print(df)

    pd.DataFrame.to_csv(df, "movies.csv", index="false")


format1()
format2()