HEADER
------
Filename: readMe.txt
Author: Parker Hague
Course: Operating Systems - CS4323
Assignment: Assignment01
Due: Feb. 23rd, 2021, 11:59 PM
Submitted: Feb 23rd, 2021
    

ABOUT
-----
This program reads in a file items.txt and stores its contents into a struct array 
which is then mapped into shared memory. The program then creates children processes 
to send and receive gift items through a message queue. The items are then printed to and
output file


USAGE
-----

*NOTE*
The order entered should be in capital letters and entered as if 
the sequence always begins with 'A' before it is scrambled e.q 'CDAB'
*NOTE*

*NOTE*
I have the helper process sleep for 5 seconds. Things sometimes don't work 
as well if I have it run immediately.
*NOTE*

*NOTE*
This program seems to work perfect the first few runs , but then starts
to do weird things sometimes after the 5 execution or so.
*NOTE*



TO COMPILE
----------

gcc -o assignment01 assignment01_Hague_Parker_main.c assignment01_Hague_Parker_customerProcess.c
assignment01_Hague_Parker_helperProcess.c  assignment01_Hague_Parker_process.c  
assignment01_Hague_Parker_readFile.c assignment01_Hague_Parker_stringOps.c -lrt

TO RUN
----------
./assignment01