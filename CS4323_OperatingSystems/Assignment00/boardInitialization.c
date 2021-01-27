// header file containing program function definitions and library imports
#include "functions.h"

char **gameBoard;

void boardInitialization(){

    gameBoard = malloc(sizeof(char *) * height);

    int i;
    // iterates through file and writes to gameBoard array
    for (i = 0; i < height; i++){

        gameBoard[i] = malloc(sizeof(char) * width);
    }
}