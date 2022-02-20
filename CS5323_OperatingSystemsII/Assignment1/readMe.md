# Operating Systems II
## Assignment 1
Parker Hague


### About
Program read a user specified .txt file and generates a histogram
for each line in the .txt file. The program uses threads in a 
threadpool to carry out the tasks of reading the file and 
creating each histogram. 

### Contents

assignment1.c - main .c file with the assignment's source code
Makefile - optional file to make compilation quicker and easier
readMe - this

### Usage

**Makefile**
make p && ./p

if not using makefile, then compilation is like a normal .c program


### Input Parameters
1. filepath of .txt file
2. number of threads between 2 and 4 inclusive