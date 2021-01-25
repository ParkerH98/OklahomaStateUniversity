// header file containing program function definitions and library imports
#include "functions.h"
#include <ctype.h>

// constants for height and width of array for reading file
#define WIDTH  100
#define HEIGHT 100

// 2d array representing the gameboard
char gameBoardTemp[HEIGHT][WIDTH];
char gameBoard[HEIGHT][WIDTH];

int *gamePtr = &gameBoard;

// initializes variables for height, width, and nested loops
int height, width, i, j;

// reads the state.txt file to initialize the gameBoard
void boardInitialization(){

    // used to keep track of index for copying over temp gameboard to actual gameboard
    int iCount, jCount = 0;

    // initializes file object and assigns a pointer 'f'
    FILE *f;

    // reads file and stores into pointer f
    f = fopen("state.txt", "r");

    // gets height and width from first line of state.txt
    fscanf(f, "%d%d", &height, &width);

    // iterates through file and writes to gameBoard array
    for(i = 0; i < height; i++){

        // reset jcount to 0 at the beginning of each outer loop
        jCount = 0;

        // iterates over columns
        for (j = 0; j < (width * 2) + 2; j++){

            // keeps jCount from going over 4
            if (jCount == 5){
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
}

// prints the gameboard as it's formatted in the .txt file
void printBoardSpaces(){

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < (width * 2) + 2; j++){

            // prints each char in gameBoard
            printf ("%c", gameBoardTemp[i][j]);
        }

        printf("\n");
    }
}

// prints the gameboard as it's formatted in the .txt file
void printBoardNoSpaces(){

    // nested loop to iterate through the board
    for(i = 0; i < 5; i++){ 

        for(j = 0; j < 5; j++){

            // prints each char in gameBoard
            printf ("%c", gameBoard[i][j]);
        }

        printf("\n");
    }
}



