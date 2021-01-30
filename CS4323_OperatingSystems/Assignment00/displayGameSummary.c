// header file containing program function definitions and library imports
#include "functions.h"

void writeToGameLog(){

    info.numGenerations = currGenCount + 1;

    // initializes file object and assigns a pointer 'f'
    FILE *f;
    // reads file and stores into pointer f
    f = fopen("GameLog.txt", "r+");
    fseek(f, 0, SEEK_END);
    fprintf(f, "PLAYER NAME: %s\nDATE: %s\nNUMBER OF GENERATIONS: %d\n---------------------------------------------------\n", info.playerName, info.date, info.numGenerations);
    printf("");
    fclose(f);
}

void displayGameLog(){

    // initializes file object and assigns a pointer 'f'
    FILE *fptr;
    // reads file and stores into pointer f
    fptr = fopen("GameLog.txt", "r");

    // Read contents from file 
    char c = fgetc(fptr); 
    while (c != EOF) 
    { 
        printf("%c", c); 
        c = fgetc(fptr); 
    } 
  
    fclose(fptr);
}