import re
import pandas as pd

def getData():
    movieFields = ['id', 'title', 'vote_average', 'vote_count', 'genres']
    castFields = ['id', 'cast']

    movieData = pd.read_csv('data_files/movies_metadata.csv', skipinitialspace=True, usecols=movieFields, engine='python')
    castData = pd.read_csv('data_files/credits.csv', skipinitialspace=True, usecols=castFields, engine='python')

    dfMovies = pd.DataFrame(movieData)
    dfCast = pd.DataFrame(castData)

    df = pd.merge(dfMovies, dfCast, how='inner')


    # ---------------------------------------------------------------------------- #
    # The following section formats the cast and creates a clean list of actor names.

    unformattedNames = df['cast']

    # main list of cast grouped by movies
    cast_master_copy = []

    # list of overall cast by individual names
    actor_name_list = []

    # reads through the cast string for each movie
    for unformattedNameString in unformattedNames:

        # creates new list for current movie
        grouped = ""

        # pulls actors' names out of the paragraph
        line_list = re.findall("(?<=\'name\': )(.*?)(?=,)", unformattedNameString)
        
        # converts list of cast for one movie into a string to manipulate further 
        line_string = str(line_list)

        # separates cast into a unique list per movie
        line_split = line_string.split(", ")

        actor_count = 0
        # reads through each actor per movie
        for name in line_split:
            if (actor_count == 5):
                break
        
            # removes extraneous symbols from the actors' names
            name = name.replace("\"", "")
            name = name.replace("\'", "")
            name = name.replace("[", "")
            name = name.replace("]", "")
            name = name.replace(" ", "")

            # adds actors to two working lists
            # grouped: actors are in lists by movies
            # actor_name_list: puts every actors in one list
            grouped += name + ' '
            actor_name_list.append(name)
            
            actor_count += 1

        # adds formatted cast members to list
        grouped = grouped[:-1]
        cast_master_copy.append(grouped)

    # assigns formatted cast to 'cast' column of DataFrame
    df['cast'] = cast_master_copy
    # ---------------------------------------------------------------------------- #


    # ---------------------------------------------------------------------------- #
    # The following section formats the genre and adds it to the data frame

    unformatted_genres = df['genres']

    # main list of genres grouped by movies
    genre_master_copy = []

    # list of overall cast by individual names
    genre_name_list = []

    # reads through the genre string for each movie
    for unformatted_genre_string in unformatted_genres:

        # creates new list for current movie
        genre_grouped = []

        # pulls genres out of the paragraph
        genre_line_list = re.findall("(?<=\'name\': )(.*?)(?=})", unformatted_genre_string)

        # converts list of genres for one movie into a string to manipulate further 
        genre_line_string = str(genre_line_list)

        # separates genre into a unique list per movie
        genre_line_split = genre_line_string.split(", ")

        # reads through each genre per movie & grabs the first one
        for genre in genre_line_split:
        
            # removes extraneous symbols from the genres
            genre = genre.replace("\"", "")
            genre = genre.replace("\'", "")
            genre = genre.replace("[", "")
            genre = genre.replace("]", "")

            genre_str = str(genre)
            break

        # adds formatted genre to list
        genre_master_copy.append(genre_str)

    # assigns formatted cast to 'cast' column of DataFrame
    df['genres'] = genre_master_copy
    # ---------------------------------------------------------------------------- #


    # ---------------------------------------------------------------------------- #
    # The following section appends the genre to the cast string. This preparation is 
    # needed for text vectorization / embedding.

    final_format_col = []
    cast = df['cast'].to_list()
    genres = df['genres'].to_list()

    i = 0
    count = len(cast)
    for i in range(count):
        final_string = genres[i] + " " + cast[i]
        final_format_col.append(final_string)

    df.insert(loc=0, column='training_col', value=final_format_col)
    df.training_col = final_format_col
    # ---------------------------------------------------------------------------- #


    # ---------------------------------------------------------------------------- #
    # The following section filters out data points that will be harmful for
    # our model's accuracy and drops unnecessary columns.

    # gets rid of all movies with 0 votes
    # Number of movies before operation: 43019
    # Number of movies after operation: 22651
    df = df.drop(df[df.vote_count < 10].index)
    # ---------------------------------------------------------------------------- #


    # ---------------------------------------------------------------------------- #
    # The following section handles the creation of the .csv files that will be the
    # primary data used to train the models. 

    # writes formatted DataFrame values to a new csv
    pd.DataFrame.to_csv(df, "formatted_movies.csv", index="false")

    # creates a csv of the actor dictionary
    # w = csv.writer(open("actor_dict.csv", "w"))
    # for key, val in actor_dict.items():
    #     w.writerow([key, val])
    # ---------------------------------------------------------------------------- #
    return df