#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



extern int active;
extern char *ptr;
extern int currGenCount;

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

// boardInitialization.c
void boardInitialization();
void freeBoard();

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
void runGenerations(int numGenerations);
void runAdditionalGenerations();
void runGenerationsAdditionally(int numGenerations);
void checkIfAllInactive();
int checkIfAllInactiveHelper();
void endGame();

// displayGenerations.c
void displayGeneration();
int countActiveNeighbors(int rowIndex, int colIndex);

// readPlayersInformation.c
void readPlayersInformation();

// displayGameSummary.c
void writeToGameLog();
void displayGameLog();

void test();