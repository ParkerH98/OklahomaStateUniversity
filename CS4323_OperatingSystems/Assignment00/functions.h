#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


extern char gameBoard[100][100];



void playerInfo();
void boardInitialization();
void printBoardSpaces();
void printBoardNoSpaces();
int isActive(char cellContents);
void test();