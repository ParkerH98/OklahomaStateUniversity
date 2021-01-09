import re
import pandas as pd
from collections import defaultdict


movieFields = ['id', 'title', 'vote_average']
castFields = ['id', 'cast']

movieData = pd.read_csv('../archive/movies_metadata.csv', skipinitialspace=True, usecols=movieFields)
castData = pd.read_csv('../archive/credits.csv', skipinitialspace=True, usecols=castFields)

dfMovies = pd.DataFrame(movieData)
dfCast = pd.DataFrame(castData)

df = pd.merge(dfMovies, dfCast, how='inner')

unformattedNames = df['cast']

# main list of cast sorted by movies
cast = []

# list of overall cast
all_names = []

# reads through the cast for each movie
for row in unformattedNames:

    # creates new list for current movie
    grouped = []

    # pulls actors' names out of the paragraph
    line = re.findall("(?<=\'name\': )(.*?)(?=,)", row)

    # converts list of cast for one movie into a string to manipulate further 
    line_string = str(line)

    # separates cast into a unique list per movie
    line_split = line_string.split(", ")

    # reads through each actor per movie
    for name in line_split:
     
        # removes extraneous symbols from the actors' names
        name = name.replace("\"", "")
        name = name.replace("\'", "")
        name = name.replace("[", "")
        name = name.replace("]", "")

        # adds actors to two working lists
        # grouped: actors are in lists by movies
        # all_names: puts every actors in one list
        grouped.append(name)
        all_names.append(name)

    # adds formatted cast members to list
    cast.append(grouped)

# assigns formatted cast to 'cast' column of DataFrame
df['cast'] = cast




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


cast_movies_names = df['cast']
cast_movies_keys = []


for cast in cast_movies_names:
    # actors = thing.split(', ')

    temp_actor_list = []

    for actor in cast:
        actor = actor.replace("[", "")
        actor = actor.replace("]", "")
        actor = actor.replace("\'", "")

        actor_key = actor_dict_inv.get(actor)
        temp_actor_list.append(actor_key)

    cast_movies_keys.append(temp_actor_list)

df['cast_ids'] = cast_movies_keys



# ensure correct
print(df)

# writes formatted DataFrame values to a new csv
pd.DataFrame.to_csv(df, "movies.csv", index="false")
