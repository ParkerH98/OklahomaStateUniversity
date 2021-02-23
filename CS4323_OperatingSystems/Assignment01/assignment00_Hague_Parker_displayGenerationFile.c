/*
Filename: displayGeneration.c
Author: Parker Hague
Course: Operating Systems - CS4323
Assignment: Assignment00
Due: Feb. 4th, 2021, 11:59 PM
Submitted: Feb. 4th, 2021

This file contains functions for printing the game board including 
printing the board and printing the board with the counts of active
neighbors.
*/

// header file containing program function definitions and library imports
#include "functions.h"

// prints the current game board to the console
// Arguments: a pointer to the gameboard and arraycopy and ints for the height and width of the gameboard
void displayGeneration(char ** gameBoard, char **arrayCopy, int height, int width){

    int i, j;

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < width; j++){

            // prints each char in gameBoard
            printf ("%c", *(*(gameBoard + i) + j));
        }

        printf("\n");
    }
    printf("\n");
}

// prints a 2d array of the number of active neighbors for each cell
// Arguments: a pointer to the arraycopy and ints for the height and width of the gameboard
void printActiveCount(char **arrayCopy, int height, int width){

    int i, j;

    // nested loop to iterate through the board
    for(i = 0; i < width; i++){ 

        for(j = 0; j < height; j++){

            // prints each char in gameBoard
            printf ("%d", countActiveNeighbors(arrayCopy, height, width, i, j));
        }

        printf("\n");
    }
    printf("\n");
}