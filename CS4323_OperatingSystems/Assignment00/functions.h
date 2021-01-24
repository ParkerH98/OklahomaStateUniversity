#include <assert.h>
#include "stdio.h"
#include <stdlib.h>
#include "time.h"





void playerInfo(){

    char playerName[30];

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[64];
    assert(strftime(date, sizeof(date), "%c", tm));
    
    printf("Please input your name.\n");
    scanf("%s", playerName);

    printf("UserName: %s\nDate: %s", playerName, date);
}