HEADER
------
Filename: readMe.txt
Author: Parker Hague
Course: Operating Systems - CS4323
Assignment: Assignment00
Due: Feb. 4th, 2021, 11:59 PM
Submitted: Nov. 30th, 2020
    

ABOUT
-----
This program reads in a file, 'state.txt', and then proceeds to store the contents of the file
into a 2d array. The program then applies a series of rules to determine the state of the gameboard.
When the program is done, a game log will print to the console consisting of the history of the game including
player name, the date, and the number of generations that the game ran.


USAGE
-----

*NOTE*
The game will automatically record the time for the user. There will not be a prompt for
the user to enter the date.
*NOTE*

*NOTE*
The game produces and uses a file called GameLog.txt to write and read struct data used in the program.
*NOTE*

TO COMPILE
----------
gcc -o assignment00 assignment00_Hague_Parker_mainFile.c assignment00_Hague_Parker_playerInfoFile.c
assignment00_Hague_Parker_boardInitializationFile.c assignment00_Hague_Parker_generationsFile.c
assignment00_Hague_Parker_displayGenerationFile.c assignment00_Hague_Parker_readPlayersInformationFile.c
assignment00_Hague_Parker_displayGameSummaryFile.c

TO RUN
----------
./assignment00