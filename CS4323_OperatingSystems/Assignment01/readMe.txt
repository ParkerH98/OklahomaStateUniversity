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
gcc -o assignment00 assignment00_Hague_Parker_mainFile.c assignment00_Hague_Parker_playerInfoFile.c
assignment00_Hague_Parker_boardInitializationFile.c assignment00_Hague_Parker_generationsFile.c
assignment00_Hague_Parker_displayGenerationFile.c assignment00_Hague_Parker_readPlayersInformationFile.c
assignment00_Hague_Parker_displayGameSummaryFile.c

TO RUN
----------
./assignment01