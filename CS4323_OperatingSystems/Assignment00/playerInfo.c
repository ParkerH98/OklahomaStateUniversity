// header file containing program function definitions and library imports
#include "functions.h"
#include "time.h"

extern char date[64];



void playerInfo(){

    char playerName[30];

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[64];
    assert(strftime(date, sizeof(date), "%c", tm));
    
    printf("\nPlease input your name.\n");
    scanf("%s", playerName);

    printf("\nUserName: %s\nDate: %s\n", playerName, date);
}




