// header file containing program function definitions and library imports
#include "functions.h"



int isActive(char cellContents){

    if (cellContents == 'X'){
        return 1;
    }
    else return 0;
}


void test(){

    printf("%d", isActive(gameBoard[0][1]));
}

void rule1(){

    for (int i = 0; i < sizeof(gameBoard); i++){

        for (int j = 0; j < sizeof(gameBoard); j++){



        
        }
    }
}


int inBounds(int row, int col){

    int bounds = 1;

    if (row < 0 || row >= sizeof(gameBoard) || col < 1 || col >= sizeof(gameBoard)){

        bounds = false;
    }

    return bounds;
}

int countActiveNeighbors(){

    int count, rowPos, colPos;
    int row, col = 0;

    for (int row = 0; row < sizeof(gameBoard); row++){

        for (int col = 0; col < sizeof(gameBoard); col++){

            count, rowPos, colPos = 0;

            for (int i = -1; i < 2; i++){
                for (int j = -1; j < 2; j++){

                    rowPos = row + i;
                    colPos = col + j;

                    if (inBounds(rowPos, colPos) == 1){
                        if (isActive(gameBoard[rowPos][colPos]) == 1){
                            count++;
                        }
                        else continue;
                    }
                    else continue;

                }
            }
        }
    }
    return count;
}

