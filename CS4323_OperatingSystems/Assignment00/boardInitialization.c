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

// double pointers to arrays
char **gameBoard;
char **arrayCopy;

// dynamically allocates a 2d array with the size of [height][width]
void boardInitialization(){

    // allocates an array for each row of the board
    gameBoard = malloc(sizeof(char *) * height);
    arrayCopy = malloc(sizeof(char *) * height);

    int i;
    for (i = 0; i < height; i++){

        // allocates column elements for each row array of the board
        gameBoard[i] = malloc(sizeof(char) * width);
        arrayCopy[i] = malloc(sizeof(char) * width);
    }
}

// frees dynamically allocated arrays from memory
void freeBoard(){

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