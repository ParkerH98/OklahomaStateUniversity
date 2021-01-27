// header file containing program function definitions and library imports
#include "functions.h"

int isActive(char cellContents){

    if (cellContents == 'X'){
        return 1;
    }
    else return 0;
}


void test(){

    int loopi, loopj;

    for (loopi = 0; loopi < height; loopi++){
        for (loopj = 0; loopj < width; loopj++){

            printf("%d ",isActive(gameBoard[loopi][loopj]));
        }
    }
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
                if (isActive(gameBoard[rowPos][colPos]) == 1){
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

    int i, j;

    // nested loop to iterate through the board
    for(i = 0; i < height; i++){ 

        for(j = 0; j < width; j++){

            if (countActiveNeighbors(gameBoard[i][j]) < 2)
        }

        printf("\n");
    }
    
}
