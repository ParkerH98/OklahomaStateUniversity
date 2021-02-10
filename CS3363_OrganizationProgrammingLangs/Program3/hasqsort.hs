-- Filename: hasqsort.hs
-- Author: Parker Hague
-- Course: CS3363
-- Assignment: Program3
-- Due: Oct. 3rd, 2020, 11:59 PM
-- Submitted: Oct. 3rd, 2020


-- import needed to use 'nub' function
import Data.List

-- quickSort transforms a list of elements of type 'a' into a list of the same type
quickSort :: Ord a => [a] -> [a]

-- if the list is empty, return an empty list
quickSort [] = []

-- This will use the 'low' variable to gather all the elemets of 'rest'
-- that are smaller than 'first' && 'high' will gather all of the elements
-- of 'rest' that are greater than or equal to 'first'.
-- After being recursively called, the lists 'low' and 'high' are concatenated
-- with 'first' to give a sorted list. Lastly, nub is called on the list
-- being concatenated in order to remove all of the duplicates.
quickSort (first:rest) = nub( (quickSort low) ++ [first] ++ (quickSort high))
    where
        low  = filter (< first) rest
        high = filter (>= first) rest


-- this was code I used to test quickSort
main = do
  
    putStr $ show $  nub (quickSort [1, 9, 8, 7, 6, 5, 5, 4, 4, 8, 2, 1])


-- I could not figure out how to make the program compile without the main method 
-- and the test case so I left it in there. I'm sorry.