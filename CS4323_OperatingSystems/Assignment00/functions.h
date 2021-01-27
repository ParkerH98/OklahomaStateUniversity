#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// extern char gameBoard[100][100];
extern char **gameBoard;
extern int height;
extern int width;


void playerInfo();
void boardInitialization();
void printBoardSpaces();
void printBoardNoSpaces();
int isActive(char cellContents);
void test();
int countActiveNeighbors(int rowIndex, int colIndex);
int inBounds(int row, int col);