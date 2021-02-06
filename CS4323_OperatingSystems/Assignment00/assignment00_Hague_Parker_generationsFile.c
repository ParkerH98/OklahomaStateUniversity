/*
Filename: generations.c
Author: Parker Hague
Course: Operating Systems - CS4323
Assignment: Assignment00
Due: Feb. 4th, 2021, 11:59 PM
Submitted: Feb. 4th, 2021

This file handles the application of the rules and the iteration of generations. 
Most of the flow of the program is handled in this file. 
*/

// header file containing program function definitions and library imports
#include "functions.h"

// counter variable used to keep track of the current generation.
// variable is needed for the function checkIfAllInactive()
int currGenCount = 0;

// Checks whether a given cell is active by checking for the presence of a 'X'.
// Arguments: a char that is the contents of a cell
int isActive(char cellContents){
    if (cellContents == 'X'){
        return 1;
    }
    else return 0;
}

// Checks whether a given cell is in bounds 
// Arguments: ints height and width for the gameboard and the row and col index to check 
int inBounds(int height, int width, int rowIndex, int colIndex){

    int bounds = 1;

    if (rowIndex < 0 || rowIndex >= height || colIndex < 0 || colIndex >= width){

        bounds = 0;
    }

    return bounds;
}

// checks the cells surrounding a given cell and returns the count of active neighbors
// Arguments: double char pointer to the array copy, ints height and width of the gameboard and the row and col index of the cell to check
int countActiveNeighbors(char **arrayCopy, int height, int width, int rowIndex, int colIndex){

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
            if (inBounds(height, width, rowPos, colPos) == 1){
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

// applying the specified rules to the gameboard
// Arguments: double char pointer to the gameboard and array copy, ints height and width of the gameboard and the row and col index of the cell to check
void rules(char ** gameBoard, char **arrayCopy, int height, int width){

    int i,j;

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < width; j++){

            // applies rule 1
            if (isActive(arrayCopy[i][j]) == 1 && countActiveNeighbors(arrayCopy, height, width, i, j) < 2){
                
                // sets value using pointers
                *(*(gameBoard + i) + j) = '-';
            }

            // applies rule 2
            if (isActive(arrayCopy[i][j]) == 1 && countActiveNeighbors(arrayCopy, height, width, i, j) > 3){
                
                // sets value using pointers
                *(*(gameBoard + i) + j) = '-';
            }

            // applies rule 3
            if ((isActive(arrayCopy[i][j]) == 1 && countActiveNeighbors(arrayCopy, height, width, i, j) == 2) || (isActive(arrayCopy[i][j]) == 1 && countActiveNeighbors(arrayCopy, height, width, i, j) == 3)){
                
                // sets value using pointers
                *(*(gameBoard + i) + j) = 'X';
            }

            // applies rule 4
            if (isActive(arrayCopy[i][j]) == 0 && countActiveNeighbors(arrayCopy, height, width, i, j) == 3){
                
                // sets value using pointers
                *(*(gameBoard + i) + j) = 'X';
            }
        }
    }
}

// makes a copy of the gameboard so the copy can be used as a 
// reference and the actual gameboard can be altered with each rule
// Arguments: double char pointer to the gameboard and array copy, ints height and width of the gameboard and the row and col index of the cell to check
void copyArray(char ** gameBoard, char **arrayCopy, int height, int width){

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
// Arguments: double char pointer to the gameboard and array copy, ints height and width of the gameboard and a pointer to the Info struct
void generations(char ** gameBoard, char **arrayCopy, int height, int width, struct Info *infoPtr){

    copyArray(gameBoard, arrayCopy, height, width);

    rules(gameBoard, arrayCopy, height, width);

    checkIfAllInactive(gameBoard, arrayCopy, height, width, infoPtr);
}

// runs the game the number of generations specified by the user
// Arguments: double char pointer to the gameboard and array copy, ints height and width of the gameboard, an int of number of generations and a pointer to the Info struct
void runGenerations(char ** gameBoard, char **arrayCopy, int height, int width, int numGenerations, struct Info *infoPtr){

    // prints intital generation
    printf("Initial Generation 0:\n");
    displayGeneration(gameBoard, arrayCopy, height, width);

    // prints the generations until numGenerations is reached
    for (int i = 0; i < numGenerations; i++){

        generations(gameBoard, arrayCopy, height, width, infoPtr);
        printf("Generation %d:\n", i + 1);
        displayGeneration(gameBoard, arrayCopy, height, width);
        currGenCount++;
    }
    endGame(gameBoard, arrayCopy, height, width, infoPtr);
}

// runs the game generations if the user answers 'yes' to the
// prompt to continue the game
// Arguments: double char pointer to the gameboard and array copy, ints height and width of the gameboard, an int of additional number of generations and a pointer to the Info struct
void runGenerationsAdditionally(char ** gameBoard, char **arrayCopy, int height, int width, int additionalGens, struct Info *infoPtr){
    
    for (int i = (*infoPtr).numGenerations - additionalGens; i < (*infoPtr).numGenerations; i++){

        generations(gameBoard, arrayCopy, height, width, infoPtr);
        printf("Generation %d:\n", i + 1);
        displayGeneration(gameBoard, arrayCopy, height, width);
        currGenCount++;
    }

    // calls endGame to determine if the program should write and terminate
    // or continue to the addition games prompt to keep playing
    endGame(gameBoard, arrayCopy, height, width, infoPtr);
}

// asks user how many additional generations to run
// Arguments: double char pointer to the gameboard and array copy, ints height and width of the gameboard, and a pointer to the Info struct
void runAdditionalGenerations(char **gameBoard, char **arrayCopy, int height, int width, struct Info *infoPtr){

    int additional;

    printf("\nHow many more generations would you like to see?\n");

    scanf("%d", &additional);

    // now sets the value of numGenerations to reflect the additional generations
    infoPtr->numGenerations = infoPtr->numGenerations + additional;

    // passes the number of additional generations to runGenerationsAdditionally to run the generations
    runGenerationsAdditionally(gameBoard, arrayCopy, height, width, additional, infoPtr);
}

// iterates through the game board and returns a 1 if the presence 
// of an 'X' is detected and a 0 if the whole board is inactive :
// function is called and used by checkIfAllInactive
// Arguments: double char pointer to the gameboard and array copy, ints height and width of the gameboard
int checkIfAllInactiveHelper(char ** gameBoard, char **arrayCopy, int height, int width){

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
// Arguments: double char pointer to the gameboard and array copy, ints height and width of the gameboard, and a pointer to the Info struct
void checkIfAllInactive(char ** gameBoard, char **arrayCopy, int height, int width, struct Info *infoPtr){

    int active = checkIfAllInactiveHelper(gameBoard, arrayCopy, height, width);

    if (active == 0){

        printf("Generation %d:\n", currGenCount + 1);
        displayGeneration(gameBoard, arrayCopy, height, width);

        printf("After %d generation, all cells in the board are inactive.\n\n", currGenCount + 1);

        // this only needs to be done when the generation is all inactive and terminates early
        (*infoPtr).numGenerations = currGenCount + 1;

        // calls endGame and begins process of writing to file and displaying game log
        endGame(gameBoard, arrayCopy, height, width, infoPtr);
    }
}

// function is called to start to end game process
// Arguments: double char pointer to the gameboard and array copy, ints height and width of the gameboard, and a pointer to the Info struct
void endGame(char **gameBoard, char **arrayCopy, int height, int width, struct Info *infoPtr){

    // is it better to have an int rep the active state or just do another function call to get the state

    // checks if the whole board is inactive : if so, write to file, 
    // display the game log, and then terminate the program
    if (checkIfAllInactiveHelper(gameBoard, arrayCopy, height, width) == 0){
        writeToGameLog(infoPtr);
        readPlayersInformation(infoPtr);
        exit(0);
    }

    char answer[4];

    printf("Would you like to display additional generations?\n");
    scanf("%s", answer);

    // run the additional generations if the user wants to
    if (strcmp(answer, "yes") == 0){
        runAdditionalGenerations(gameBoard, arrayCopy, height, width, infoPtr);
    }

    // starts the end game process of writing to file and displaying game log
    else{
        writeToGameLog(infoPtr);
        freeBoard(gameBoard, arrayCopy, height, width);
        readPlayersInformation(infoPtr);
        exit(0);
    }
}