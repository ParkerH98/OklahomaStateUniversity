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
    char playerName[256];
    char date[256];
    int numGenerations;
};

// playerInfo.c
void playerInfo();

// boardInitialization.c
char ** boardInitialization();
char ** boardCopyInitialization();
void freeBoard(char **gameBoard, char **arrayCopy, int height, int width);

// generations.c
void runGenerations(char ** gameBoard, char **arrayCopy, int height, int width, int numGenerations, struct Info *infoPtr);
void checkIfAllInactive(char ** gameBoard, char **arrayCopy, int height, int width, struct Info *infoPtr);
void endGame(char **gameBoard, char **arrayCopy, int height, int width, struct Info *infoPtr);

// displayGenerations.c
void displayGeneration(char ** gameBoard, char **arrayCopy, int height, int width);
int countActiveNeighbors(char **arrayCopy, int height, int width, int rowIndex, int colIndex);

// readPlayersInformation.c

void readInGameFile();
void readPlayersInformation(struct Info *infoPtr);

// displayGameSummary.c
void writeToGameLog();
void displayGameSummary(struct Info *players);