/*
Filename: playerInfo.c
Author: Parker Hague
Course: Operating Systems - CS4323
Assignment: Assignment00
Due: Feb. 4th, 2021, 11:59 PM
Submitted: Feb. 4th, 2021

This file serves to get the user information for the game
including their name, the date, and the number of generations desired
*/

// header file containing program function definitions and library imports
#include "functions.h"


// gets player info and saves into a Info struct
void playerInfo(){
    // instantiates an Info object to store player info
    struct Info info;
    struct Info *infoPtr;

    infoPtr = &info;

    // gets and formats the date and then saves into a char[]
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(info.date, sizeof(info.date), "%A, %B %d, %Y - %I:%M %p", tm);
    
    // gets player name from input
    printf("\nPlease input your name.\n");
    fgets((*infoPtr).playerName, 30, stdin);
    strtok((*infoPtr).playerName, "\n");

    // gets the number of generations from input
    printf("\nHow many generations would you like to see initially?.\n");
    scanf("%d", &(infoPtr -> numGenerations));

    readInGameFile(infoPtr);
}