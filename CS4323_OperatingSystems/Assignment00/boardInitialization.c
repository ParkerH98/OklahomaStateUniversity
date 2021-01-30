/* 
This file creates and frees the arrays needed in this program.
*/

// header file containing program function definitions and library imports
#include "functions.h"

char **gameBoard;
char **arrayCopy;


void boardInitialization(){

    gameBoard = malloc(sizeof(char *) * height);
    arrayCopy = malloc(sizeof(char *) * height);

    int i;
    // iterates through file and writes to gameBoard array
    for (i = 0; i < height; i++){

        gameBoard[i] = malloc(sizeof(char) * width);
        arrayCopy[i] = malloc(sizeof(char) * width);

    }

    char *ptr;
    ptr = *gameBoard;
}


void freeBoard(){

    int i;

    for (i = 0; i < height; i++){  

       free(gameBoard[i]); 
       free(arrayCopy[i]);
    }   

    free(gameBoard);
    free(arrayCopy);

}