// header file containing program function definitions and library imports
#include "functions.h"
#include <stdio.h>


void hh(){
    // initializes file object and assigns a pointer 'f'
    FILE *f;

    // reads file and stores into pointer f
    f = fopen("GameLog.txt", "r+");
    fseek(f, 0, SEEK_END);
    fprintf(f, "PLAYER NAME: %s\nDATE: %s\nNUMBER OF GENERATIONS: %d\n---------------------------------------------------\n", info.playerName, info.date, info.numGenerations);
    printf("");
}

void endGame(){

    char answer[3];
    int isContinueing = 0;

    printf("Would you like to display additional generations?\n");
    scanf("%s", answer);

    if (strcmp(answer, "yes") == 0){
        runAdditionalGenerations();
        isContinueing = 1;
    }
    else{

        hh();
    }

}


void runAdditionalGenerations(){

    int additional;

    printf("\nHow many more generations would you like to see?\n");

    scanf("%d", &additional);
    info.numGenerations = info.numGenerations + additional;

    runGenerationsAdditionally(additional);
}