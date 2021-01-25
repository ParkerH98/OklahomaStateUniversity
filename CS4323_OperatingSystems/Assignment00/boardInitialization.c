// header file containing program function definitions and library imports
#include "functions.h"

// constants for height and width of array for reading file
#define WIDTH  100
#define HEIGHT 100

// 2d array representing the gameboard
char gameBoard[HEIGHT][WIDTH];

// initializes variables for height, width, and nested loops
int height, width, i, j;

// reads the state.txt file to initialize the gameBoard
void boardInitialization(){

    // initializes file object and assigns a pointer 'f'
    FILE *f;

    // reads file and stores into pointer f
    f = fopen("state.txt", "r");

    // gets height and width from first line of state.txt
    fscanf(f, "%d%d", &height, &width);

    // iterates through file and writes to gameBoard array
    for(i = 0; i < height; i++){

        for (j = 0; j < (width * 2) + 2; j++){

            fscanf(f, "%c", &gameBoard[j][i]);
        }
    }
    // closes the file stream
    fclose(f);
}

// prints the gameBoard
void printBoard(){

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < (width * 2) + 2; j++){

            // prints each char in gameBoard
            printf ("%c", gameBoard[j][i]);
        }

        printf("\n");
    }
}