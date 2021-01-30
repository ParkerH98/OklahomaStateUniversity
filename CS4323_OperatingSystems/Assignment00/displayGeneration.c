// header file containing program function definitions and library imports
#include "functions.h"

// prints the gameboard as it's formatted in the .txt file
void displayGeneration(){

    int i, j;

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < width; j++){

            // prints each char in gameBoard
            printf ("%c", gameBoard[i][j]);
        }

        printf("\n");
    }
    printf("\n");
}

//debug function no actual use
void printActiveCount(){

    int i, j;

    // nested loop to iterate through the board
    for(i = 0; i < width; i++){ 

        for(j = 0; j < height; j++){

            // prints each char in gameBoard
            printf ("%d", countActiveNeighbors(i, j));
        }

        printf("\n");
    }
    printf("\n");
}