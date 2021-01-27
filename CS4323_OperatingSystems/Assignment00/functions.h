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




// generations.c
int isActive(char cellContents);
void printActiveCount();
int inBounds(int row, int col);
void rule1();
void rule2();
void rule3();
void rule4();
void generations();

// displayGenerations.c
void displayGeneration();
int countActiveNeighbors(int rowIndex, int colIndex);

// readPlayersInformation.c
void readPlayersInformation();
