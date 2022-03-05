# Operating Systems II
## Assignment 1

### Author
Parker Hague
phague@okstate.edu


### About
Program read a user specified .txt file and generates a histogram
for each line in the .txt file. The program uses threads in a 
threadpool to carry out the tasks of reading the file and 
creating each histogram. 


### Contents
- assignment1.c - main .c file with the assignment's source code
- Makefile - optional file to make compilation quicker and easier
- readMe - this


### Usage
#### CSX Compilation
    gcc assignment1.c -o parker -pthread
    ./parker
#### Makefile (not on csx)
    make p && ./p


#### Input Parameters
1. filepath of .txt file
2. number of threads between 2 and 4 inclusive