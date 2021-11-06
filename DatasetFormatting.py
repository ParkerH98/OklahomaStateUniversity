import re
import pandas as pd
from collections import defaultdict




movieFields = ['id', 'title', 'vote_average', 'vote_count', 'genres']
castFields = ['id', 'cast']

movieData = pd.read_csv('archive/movies_metadata.csv', skipinitialspace=True, usecols=movieFields)
castData = pd.read_csv('archive/credits.csv', skipinitialspace=True, usecols=castFields)

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
# The following section turns the list of actor names into a list of unique numbers
# assigned to those actors. Then, creates a dictionary with the actor names and those 
# keys.

# initializes default dictionary
key_assignment = defaultdict(lambda: len(key_assignment))

# list of unique keys for each actor in dictionary
keys = [key_assignment[key] for key in actor_name_list]

# assigns keys to actors to form a hash table...nums are keys
actor_dict = dict(zip(keys, actor_name_list))

# inverts dictionary...names are keys
actor_dict_inv = {v: k for k, v in actor_dict.items()}
# ---------------------------------------------------------------------------- #


# ---------------------------------------------------------------------------- #
# The following section uses the inverted actor dictionary to look up the actor names
# and put their respective dictionary values in a list for each movie.

cast_names_by_movie = df['cast']
cast_ids_by_movie_master = []

for cast in cast_names_by_movie:

    temp_actor_list = []

    for actor in cast:
        actor = actor.replace("[", "")
        actor = actor.replace("]", "")
        actor = actor.replace("\'", "")

        actor_key = actor_dict_inv.get(actor)
        temp_actor_list.append(actor_key)
    
    if (len(temp_actor_list) < 5):
            diff = 5 - len(temp_actor_list)
            
            for i in range(diff):
                temp_actor_list.append(1)

    cast_ids_by_movie_master.append(temp_actor_list)

df['cast_ids'] = cast_ids_by_movie_master
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
# The following section filters out data points that will be harmful for
# our model's accuracy.

# gets rid of all movies with 0 votes
# Number of movies before operation: 43020
# Number of movies after operation: 40739
df = df.drop(df[df.vote_count < 10].index)
# ---------------------------------------------------------------------------- #


# ---------------------------------------------------------------------------- #
# The following section handles the creation of the .csv files that will be the
# primary data used to train the models. 

# writes formatted DataFrame values to a new csv
# pd.DataFrame.to_csv(df, "formatted_movies.csv", index="false")

# creates a csv of the actor dictionary
# w = csv.writer(open("actor_dict.csv", "w"))
# for key, val in actor_dict.items():
#     w.writerow([key, val])
# ---------------------------------------------------------------------------- #

# print(df)




#-----------------------------------------------------------------------------
#                Appends genres to cast string
#-----------------------------------------------------------------------------
final_format_col = []
cast = df['cast'].to_list()
genres = df['genres'].to_list()

i = 0
count = len(cast)
for i in range(count):
    final_string = cast[i] + " " + genres[i]
    final_format_col.append(final_string)


df.insert(loc=0, column='final_form', value=final_format_col)
df.final_form = final_format_col
# print(df.final_form)