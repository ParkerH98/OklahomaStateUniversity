Operating Systems II
## Assignment 4


### Author
Parker Hague
phague@okstate.edu


### About
This program simulates the FIFO and LRU page replacement algorithms
on a set of real world trace fils of memory accesses. 


### Contents
- parker.c - main .c file with the assignment's source code
- readMe - this


### Usage
#### Compilation
    gcc parker.c -o p
	./p <tracefile> <number of frames> <fifo|lru>

#### Example Usage
    gcc parker.c -o p
	./p bzip.txt 4 lru

#### Makefile Usage
    make test


#### Input Parameters
1. .txt tracefile
2. number of page frames in working set
3. replacement algorithm (FIFO or LRU)