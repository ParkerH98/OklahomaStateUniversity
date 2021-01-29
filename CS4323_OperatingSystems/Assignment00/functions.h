#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


extern char *ptr;

extern int isContinueing;
extern int additional;

struct Info{
    char playerName[30];
    char date[64];
    int numGenerations;
};

extern struct Info info;

extern char **gameBoard;
extern char **arrayCopy;

extern int height;
extern int width;

extern char playerName[30];
extern char date[64];
extern int numGenerations;


// playerInfo.c
void playerInfo();
// void generationPrompt();


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
void copyArray();

// displayGenerations.c
void displayGeneration();
int countActiveNeighbors(int rowIndex, int colIndex);

// readPlayersInformation.c
void readPlayersInformation();
void printBoardSpaces();

void print();
void test();

void runGenerations(int numGenerations);
void endGame();
void hh();
void runAdditionalGenerations();

void runGenerationsAdditionally(int numGenerations);