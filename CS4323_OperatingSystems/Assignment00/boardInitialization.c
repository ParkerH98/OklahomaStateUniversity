/* 
Filename: boardInitialization.c
Author: Parker Hague
Course: Operating Systems - CS4323
Assignment: Assignment00
Due: Feb. 4th, 2021, 11:59 PM
Submitted: Nov. 30th, 2020

This file creates and frees the arrays needed in this program.
*/

// header file containing program function definitions and library imports
#include "functions.h"

// dynamically allocates a 2d array with the size of [height][width]
char ** boardInitialization(int height, int width){

    // double pointers to arrays
    char **gameBoard;

    // allocates an array for each row of the board
    gameBoard = malloc(sizeof(char *) * height);

    int i;
    for (i = 0; i < height; i++){

        // allocates column elements for each row array of the board
        gameBoard[i] = malloc(sizeof(char) * width);
    }
    return gameBoard;
}

char ** boardCopyInitialization(int height, int width){

    // double pointers to arrays
    char **arrayCopy;

    // allocates an array for each row of the board
    arrayCopy = malloc(sizeof(char *) * height);

    int i;
    for (i = 0; i < height; i++){

        // allocates column elements for each row array of the board
        arrayCopy[i] = malloc(sizeof(char) * width);
    }

    return arrayCopy;
}

// frees dynamically allocated arrays from memory
void freeBoard(char **gameBoard, char **arrayCopy, int height, int width){

    int i;
    // frees column elements first
    for (i = 0; i < height; i++){  

       free(gameBoard[i]); 
       free(arrayCopy[i]);
    }   

    // frees remaining array (rows)
    free(gameBoard);
    free(arrayCopy);
}