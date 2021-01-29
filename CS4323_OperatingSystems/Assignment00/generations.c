// header file containing program function definitions and library imports
#include "functions.h"

int isActive(char cellContents)
{

    if (cellContents == 'X'){
        return 1;
    }
    else return 0;
}

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
}

void runGenerations(int numGenerations){

    printf("Generation 0:\n");
    displayGeneration();


    for (int i = 0; i < numGenerations; i++){

        generations();
        printf("Generation %d:\n", i + 1);
        displayGeneration();
    }
}

void runGenerationsAdditionally(int additionalGens){

    for (int i = info.numGenerations - additionalGens; i < info.numGenerations; i++){

        generations();
        printf("Generation %d:\n", i + 1);
        displayGeneration();
    }

    endGame();
}
