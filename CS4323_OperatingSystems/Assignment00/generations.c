/*
Filename: generations.c
Author: Parker Hague
Course: Operating Systems - CS4323
Assignment: Assignment00
Due: Feb. 4th, 2021, 11:59 PM
Submitted: Nov. 30th, 2020

This file handles the application of the rules and the iteration of generations. 
Most of the flow of the program is handled in this file. 
*/

// header file containing program function definitions and library imports
#include "functions.h"

// counter variable used to keep track of the current generation.
// variable is needed for the function checkIfAllInactive()
int currGenCount = 0;

// Checks whether a given cell is active by checking for the presence of a 'X'.
int isActive(char cellContents){
    if (cellContents == 'X'){
        return 1;
    }
    else return 0;
}

// Checks whether a given cell is in bounds 
int inBounds(int rowIndex, int colIndex){

    int bounds = 1;

    if (rowIndex < 0 || rowIndex >= height || colIndex < 0 || colIndex >= width){

        bounds = 0;
    }

    return bounds;
}

// checks the cells surrounding a given cell and returns the count of active neighbors
int countActiveNeighbors(int rowIndex, int colIndex){

    int count = 0;
    int rowPos = 0;
    int colPos = 0;

    // iterates through the 8 squares around gameBoard[rowIndex][colIndex]
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){

            // continue if the iteration is on the current square (so the current square isn't counted)
            if (i == 0 && j == 0) continue;

            rowPos = rowIndex + i;
            colPos = colIndex + j;

            // iterate the count if the cell is inBounds (in the game board)
            // and if the cell is active (contains an 'X')
            if (inBounds(rowPos, colPos) == 1){
                if (isActive(arrayCopy[rowPos][colPos]) == 1){
                    count++;
                }
                else continue;
            }
            else continue;
        }
    }
    return count;
}

// implementation of rule 1
void rule1(){

    int i,j;

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < width; j++){

            if (isActive(arrayCopy[i][j]) == 1 && countActiveNeighbors(i, j) < 2){
                // gameBoard[i][j] = '-';

                *(*(gameBoard + i) + j) = '-';
            }
        }
    }
}

// implementation of rule 2
void rule2(){

    int i, j;

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < width; j++){

            if (isActive(arrayCopy[i][j]) == 1 && countActiveNeighbors(i, j) > 3){
                
                // sets value using pointers
                *(*(gameBoard + i) + j) = '-';
            }
        }
    }
}

// implementation of rule 3
void rule3(){

    int i, j;

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < width; j++){

            if ((isActive(arrayCopy[i][j]) == 1 && countActiveNeighbors(i, j) == 2) || (isActive(arrayCopy[i][j]) == 1 && countActiveNeighbors(i, j) == 3)){
                
                // sets value using pointers
                *(*(gameBoard + i) + j) = 'X';
            }
        }
    }
}

// implementation of rule 4
void rule4(){

    int i, j;

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < width; j++){

            if (isActive(arrayCopy[i][j]) == 0 && countActiveNeighbors(i, j) == 3){
                
                // sets value using pointers
                *(*(gameBoard + i) + j) = 'X';

            }
        }
    }
}

// makes a copy of the gameboard so the copy can be used as a 
// reference and the actual gameboard can be altered with each rule
void copyArray(){

    // char arrayCopy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++){
            arrayCopy[i][j] = gameBoard[i][j];

        }
    }
}

// makes a copy of the gameboard and then executes the 4 rules:
// then, checks if the board is all inactive to decide to continue 
// execution or to start the end game process
void generations(){

    copyArray();

    rule1();
    rule2();
    rule3();
    rule4();

    checkIfAllInactive();
}

// runs the game the number of generations specified by the user
void runGenerations(int numGenerations){

    // prints intital generation
    printf("Initial Generation 0:\n");
    displayGeneration();

    // prints the generations until numGenerations is reached
    for (int i = 0; i < numGenerations; i++){

        generations();
        printf("Generation %d:\n", i + 1);
        displayGeneration();
        currGenCount++;
    }
}

// runs the game generations if the user answers 'yes' to the
// prompt to continue the game
void runGenerationsAdditionally(int additionalGens){

    for (int i = info.numGenerations - additionalGens; i < info.numGenerations; i++){

        generations();
        printf("Generation %d:\n", i + 1);
        displayGeneration();
        currGenCount++;
    }

    // calls endGame to determine if the program should write and terminate
    // or continue to the addition games prompt to keep playing
    endGame();
}

// asks user how many additional generations to run
void runAdditionalGenerations(){

    int additional;

    printf("\nHow many more generations would you like to see?\n");

    scanf("%d", &additional);

    // now sets the value of numGenerations to reflect the additional generations
    info.numGenerations = info.numGenerations + additional;

    // passes the number of additional generations to runGenerationsAdditionally to run the generations
    runGenerationsAdditionally(additional);
}

// iterates through the game board and returns a 1 if the presence 
// of an 'X' is detected and a 0 if the whole board is inactive :
// function is called and used by checkIfAllInactive
int checkIfAllInactiveHelper(){

    int allInactive = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++){
            
            if (gameBoard[i][j] == 'X'){

                allInactive = 1;
                return allInactive;
            }
            else continue;
        }
    }

    return allInactive;
}

// uses checkIfAllInactiveHelper to decide if the game needs to 
// terminate after execution of the rules or continue running
void checkIfAllInactive(){

    int active = checkIfAllInactiveHelper();

    if (active == 0){

        printf("Generation %d:\n", currGenCount + 1);
        displayGeneration();

        printf("After %d generation, all cells in the board are inactive.\n\n", currGenCount + 1);

        // this only needs to be done when the generation is all inactive and terminates early
        info.numGenerations = currGenCount + 1;

        // calls endGame and begins process of writing to file and displaying game log
        endGame();
    }
}

void endGame(){

    // is it better to have an int rep the active state or just do another function call to get the state

    // checks if the whole board is inactive : if so, write to file, 
    // display the game log, and then terminate the program
    if (checkIfAllInactiveHelper() == 0){
        writeToGameLog();
        displayGameLog();
        exit(0);
    }

    char answer[3];

    printf("Would you like to display additional generations?\n");
    scanf("%s", answer);

    // run the additional generations if the user wants to
    if (strcmp(answer, "yes") == 0){
        runAdditionalGenerations();
    }

    // starts the end game process of writing to file and displaying game log
    else{
        writeToGameLog();
        freeBoard();
        displayGameLog();
        exit(0);
    }
}