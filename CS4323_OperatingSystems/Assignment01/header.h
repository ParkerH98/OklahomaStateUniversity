#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_ITEMS 100


// struct to hold player information
struct Item{
    int serialNum;
    char item[256];
    char price[64];
    char store[64];
};



void readFile();
