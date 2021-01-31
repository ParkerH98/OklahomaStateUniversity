/*
Filename: displayGameSummary.c
Author: Parker Hague
Course: Operating Systems - CS4323
Assignment: Assignment00
Due: Feb. 4th, 2021, 11:59 PM
Submitted: Nov. 30th, 2020

This file handles writing the game information to the game log
and has a function to print the log to the console.
*/

// header file containing program function definitions and library imports
#include "functions.h"

// writes the name, date, and number of generations to an output file
void writeToGameLog(){

    // initializes file object and assigns a pointer 'f'
    FILE *f;
    // reads file and stores into pointer f
    f = fopen("GameLog.txt", "r+");

    fseek(f, 0, SEEK_END);
    fprintf(f, "PLAYER NAME: %s\nDATE: %s\nNUMBER OF GENERATIONS: %d\n---------------------------------------------------\n", info.playerName, info.date, info.numGenerations);
    printf("");
    fclose(f);
}

// prints the game log to the console after the generations are done executing
void displayGameLog(){

    // initializes file object and assigns a pointer 'f'
    FILE *fptr;
    // reads file and stores into pointer f
    fptr = fopen("GameLog.txt", "r");

    printf("\n");
    
    // Read contents from file
    char c = fgetc(fptr); 
    while (c != EOF) 
    { 
        printf("%c", c); 
        c = fgetc(fptr); 
    } 
  
    fclose(fptr);
}