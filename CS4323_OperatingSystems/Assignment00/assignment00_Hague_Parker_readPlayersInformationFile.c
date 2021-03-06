/*
Filename: readPlayersInformation.c
Author: Parker Hague
Course: Operating Systems - CS4323
Assignment: Assignment00
Due: Feb. 4th, 2021, 11:59 PM
Submitted: Feb. 4th, 2021

This file reads the GameLog.txt file and stores the contents into a Info
struct array. 
*/

// header file containing program function definitions and library imports
#include "functions.h"

// constants for height and width of array for reading file
#define WIDTH  100
#define HEIGHT 100

// 2d array representing the gameboard
char gameBoardTemp[HEIGHT][WIDTH];

// initializes variables for height, width, and nested loops
int height, width, i, j;

// reads the state.txt file to initialize the gameBoard
// Arguments: an Info pointer to the info struct
void readInGameFile(struct Info *infoPtr){

    // used to keep track of index for copying over temp gameboard to actual gameboard
    int iCount, jCount = 0;

    // initializes file object and assigns a pointer 'f'
    FILE *f;

    // reads file and stores into pointer f
    f = fopen("state.txt", "r");

    // gets height and width from first line of state.txt
    fscanf(f, "%d%d", &height, &width);

    // dynamically allocates the 2d array as the game board
    char ** gameBoard = boardInitialization(height, width);
    char ** arrayCopy = boardCopyInitialization(height, width);

    // iterates through file and writes to gameBoard array
    for(i = 0; i < height; i++){

        // reset jcount to 0 at the beginning of each outer loop
        jCount = 0;

        // iterates over columns
        for (j = 0; j < (width * 2) + 2; j++){

            // keeps jCount from going over 4
            if (jCount == width){
                break;
            }

            // reads entire file into an 2d array (spaces included)
            fscanf(f, "%c", &gameBoardTemp[i][j]);

            // checks if char is not a space and a digit
            if (!isspace(gameBoardTemp[i][j]) && !isdigit(gameBoardTemp[i][j])){

                // stores into a new array: doing this to get rid of the spaces from the original file read
                gameBoard[iCount][jCount] = gameBoardTemp[i][j];
                
                jCount++;
            }
        }
        printf("\n");

        iCount++;
    }

    // closes the file stream
    fclose(f);

    runGenerations(gameBoard, arrayCopy, height, width, infoPtr->numGenerations, infoPtr);
} 

// this function reads the GameLog.txt file and stores its contents into a Info struct array
// Arguments: an Info pointer to the info struct
void readPlayersInformation(struct Info *infoPtr){

    struct Info players[100];
    FILE *f;
    f = fopen("GameLog.txt", "r");

    char line[256];

    int index = 0;
    int marker = 0;

    // goes through each line of the file and assigns it to the appropriate variables
    while(fgets(line, 256, f) != NULL)
    {
        if (marker == 0){

            strcpy(players[index].playerName, line);
            marker++;
        }

        else if (marker == 1){

            strcpy(players[index].date, line);
            marker++;
        }

        else if (marker == 2){
      
            players[index].numGenerations = atoi(line);

            marker = 0;
            index++;
        }
    }

    // passes in pointer to Info[] that contains all of the player info to print
    displayGameSummary(players);
}