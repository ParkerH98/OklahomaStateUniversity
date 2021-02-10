/*
Filename: displayGameSummary.c
Author: Parker Hague
Course: Operating Systems - CS4323
Assignment: Assignment00
Due: Feb. 4th, 2021, 11:59 PM
Submitted: Feb. 4th, 2021

This file handles writing the game information to the game log
and has a function to print the log to the console.
*/

// header file containing program function definitions and library imports
#include "functions.h"

// writes the name, date, and number of generations to an output file
// Arguments: a pointer to the info struct
void writeToGameLog(struct Info *infoPtr){

    // initializes file object and assigns a pointer 'f'
    FILE *f;
    // reads file and stores into pointer f
    f = fopen("GameLog.txt", "r+");

    fseek(f, 0, SEEK_END);
    // fprintf(f, "PLAYER NAME: %s\nDATE: %s\nNUMBER OF GENERATIONS: %d\n---------------------------------------------------\n", (*infoPtr).playerName, (*infoPtr).date, (*infoPtr).numGenerations);
    fprintf(f, "%s\n%s\n%d\n", (*infoPtr).playerName, (*infoPtr).date, (*infoPtr).numGenerations);

    printf("");
    fclose(f);
}

// prints the game log to the console from a struct array containing game info
// Arguments: a pointer to the info struct
void displayGameSummary(struct Info *players){

    for (int i = 0; i < 1000; i++){
        if (strcmp(players[i].playerName, "") == 0 ) break;
        printf("PLAYER NAME: %s\nDATE: %s\nNUMBER OF GENERATIONS: %d\n---------------------------------------------------\n", players[i].playerName, players[i].date, players[i].numGenerations);
    }
}