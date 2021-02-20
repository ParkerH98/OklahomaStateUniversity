#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_ITEMS 100

// struct to hold player information
struct Item{
    int serialNum;
    char item[256];
    char price[16];
    char store[64];
};


// extern struct Item itemsList[100];

// void foo(struct Item itemsList);
void readFile();

void test();
void test1();


