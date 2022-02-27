# Operating Systems II
## Assignment 2

### Author
Parker Hague
phague@okstate.edu


### About
Program reads a user specified .txt file line by line and populates a 
single histogram with the occurrences of characters in each line of the
file. The program uses threads in a threadpool to carry out the tasks of
reading the file and populating the histogram.


### Contents
- assignment2.c - main .c file with the assignment's source code
- Makefile - optional file to make compilation quicker and easier for myself
- readMe - this



### Usage
#### CSX Compilation
    gcc assignment2.c -o parker -pthread
    ./parker
#### Makefile
    make p && ./p



#### Input Parameters
1. filepath of .txt file
2. number of threads between 1 and 4 