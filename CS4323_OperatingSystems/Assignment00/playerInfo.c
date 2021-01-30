// header file containing program function definitions and library imports
#include "functions.h"
#include "time.h"
#include "string.h"

struct Info info;



void playerInfo(){

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    // char date[64];
    assert(strftime(info.date, sizeof(info.date), "%c", tm));
    
    printf("\nPlease input your name.\n");
    fgets(info.playerName, 30, stdin);
    strtok(info.playerName, "\n");

    printf("\nHow many generations would you like to see initially?.\n");
    scanf("%d", &info.numGenerations);
}