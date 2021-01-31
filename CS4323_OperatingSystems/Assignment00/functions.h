/*
Filename: functions.h
Author: Parker Hague
Course: Operating Systems - CS4323
Assignment: Assignment00
Due: Feb. 4th, 2021, 11:59 PM
Submitted: Nov. 30th, 2020

This file is a header file that serves to make several functions
and variables global for multi file use. Includes function prototypes,
external variable declarations, and library imports.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// struct to hold player information
struct Info{
    char playerName[30];
    char date[64];
    int numGenerations;
};

// instantiates Info object to store player info
extern struct Info info;

// makes members of the struct global
extern char playerName[30];
extern char date[64];
extern int numGenerations;

// playerInfo.c
void playerInfo();

// boardInitialization.c
extern char **gameBoard;
extern char **arrayCopy;
void boardInitialization();
void freeBoard();

// generations.c
// int isActive(char cellContents);
// void printActiveCount();
// int inBounds(int row, int col);
// void rule1();
// void rule2();
// void rule3();
// void rule4();
// void generations();
// void copyArray();
void runGenerations(int numGenerations);
// void runAdditionalGenerations();
// void runGenerationsAdditionally(int numGenerations);
void checkIfAllInactive();
// int checkIfAllInactiveHelper();
void endGame();

// displayGenerations.c
void displayGeneration();
int countActiveNeighbors(int rowIndex, int colIndex);

// readPlayersInformation.c
extern int height;
extern int width;
void readPlayersInformation();

// displayGameSummary.c
void writeToGameLog();
void displayGameLog();