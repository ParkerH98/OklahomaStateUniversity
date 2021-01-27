#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// extern char gameBoard[100][100];
extern char **gameBoard;
extern int height;
extern int width;


// playerInfo.c
void playerInfo();


// boardInitialization.c
void boardInitialization();
void printBoardSpaces();
void printBoardNoSpaces();


// generations.c
int isActive(char cellContents);
void test();
int countActiveNeighbors(int rowIndex, int colIndex);
int inBounds(int row, int col);
void rule1();