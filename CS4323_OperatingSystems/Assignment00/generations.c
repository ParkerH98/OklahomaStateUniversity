/*
Filename: FamilyMember.java
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

/*
 * Function: isActive
 * ----------------------------
 *   Checks whether a given cell is active by checking for the presence of a 'X'.
 *
 *   cellContents: char value obtained from gameBoard[i][j] 
 *
 *   returns: 1 if cell is active and 0 if inactive 
 */
int isActive(char cellContents){
    if (cellContents == 'X'){
        return 1;
    }
    else return 0;
}

/*
 * Function: inBounds
 * ----------------------------
 *   Checks whether a given cell is in bounds 
 *
 *   rowIndex: row index of the cell
 *   colIndex: col index of the cell
 * 
 *   returns: 1 if cell is in bounds and 0 if cell is out of bounds
 */
int inBounds(int rowIndex, int colIndex){

    int bounds = 1;

    if (rowIndex < 0 || rowIndex >= height || colIndex < 0 || colIndex >= width){

        bounds = 0;
    }

    return bounds;
}

int countActiveNeighbors(int rowIndex, int colIndex){

    int count = 0;
    int rowPos = 0;
    int colPos = 0;

    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){

            if (i == 0 && j == 0) continue;

            rowPos = rowIndex + i;
            colPos = colIndex + j;

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


void rule1(){

    int i,j;

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < width; j++){

            if (isActive(arrayCopy[i][j]) == 1 && countActiveNeighbors(i, j) < 2){
                gameBoard[i][j] = '-';

                // *(*(gameBoard + i) + j)) = 4;
            }
        }
    }
}

void rule2(){

    int i, j;

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < width; j++){

            if (isActive(arrayCopy[i][j]) == 1 && countActiveNeighbors(i, j) > 3){
                gameBoard[i][j] = '-';
            }
        }
    }
}

void rule3(){

    int i, j;

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < width; j++){

            if ((isActive(arrayCopy[i][j]) == 1 && countActiveNeighbors(i, j) == 2) || (isActive(arrayCopy[i][j]) == 1 && countActiveNeighbors(i, j) == 3)){
                gameBoard[i][j] = 'X';
            }
        }
    }
}

void rule4(){

    int i, j;

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < width; j++){

            if (isActive(arrayCopy[i][j]) == 0 && countActiveNeighbors(i, j) == 3){
                gameBoard[i][j] = 'X';
            }
        }
    }
}

void copyArray(){

    // char arrayCopy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++){
            arrayCopy[i][j] = gameBoard[i][j];

        }
    }
}


void print(){

    char arrayCopy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++){
            printf("%c", arrayCopy[i][j]);

        }
        printf("\n");
    }
}


void generations(){

    copyArray();

    rule1();
    rule2();
    rule3();
    rule4();

    // checkIfAllInactive();
}

void runGenerations(int numGenerations){

    printf("Generation 0:\n");
    displayGeneration();


    for (int i = 0; i < numGenerations; i++){

        generations();
        printf("Generation %d:\n", i + 1);
        displayGeneration();
        currGenCount++;
    }
}

void runGenerationsAdditionally(int additionalGens){

    for (int i = info.numGenerations - additionalGens; i < info.numGenerations; i++){

        generations();
        printf("Generation %d:\n", i + 1);
        displayGeneration();
        currGenCount++;

    }

    endGame();
}

void runAdditionalGenerations(){

    int additional;

    printf("\nHow many more generations would you like to see?\n");

    scanf("%d", &additional);
    info.numGenerations = info.numGenerations + additional;

    runGenerationsAdditionally(additional);
}



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

void checkIfAllInactive(){

    int active = checkIfAllInactiveHelper();

    if (active == 1){

        printf("After %d generation, all cells in the board are inactive.\n", currGenCount);
        endGame();
    }
}

void endGame(){

    // is it better to have an int rep the active state or just do another function call to get the state
    if (checkIfAllInactiveHelper() == 1){
        displayGameLog();
        exit(0);
    }

    char answer[3];
    int isContinueing = 0;

    printf("Would you like to display additional generations?\n");
    scanf("%s", answer);

    if (strcmp(answer, "yes") == 0){
        runAdditionalGenerations();
        isContinueing = 1;
    }

    else{

        writeToGameLog();
        freeBoard();
        displayGameLog();
        exit(0);
    }
}


void test(){

    int i, j;

    for(i = 0; i < height; i++){

        // iterates over columns
        for (j = 0; j < width ; j++){

            printf("%c", *(*(gameBoard + i) + j));
        }
    }
}