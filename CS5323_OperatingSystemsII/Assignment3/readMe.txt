 Operating Systems II
## Assignment 3

### Author
Parker Hague
phague@okstate.edu


### About
This is a reader writer solution that handles fairness. The program will allow
k+1 readers to execute the reader function where k is half the number of total readers.
After k+1 readers have entered the function, the writer is guaranteed to
get attention from the CPU in order to avoid starvation.


### Contents
- parker.c - main .c file with the assignment's source code
- readMe - this


### Usage
#### CSX Compilation
    gcc parker.c -o p -pthread -lrt -w
    ./p


#### Input Parameters
1. number of threads between 1 and 14