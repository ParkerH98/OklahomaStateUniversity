/*
Filename: main.c
Author: Parker Hague
Course: Operating Systems - CS4323
Assignment: Assignment00
Due: Feb. 4th, 2021, 11:59 PM
Submitted: Nov. 30th, 2020

This file runs the program and only consists of function calls.
*/

// header file containing program function definitions and library imports
#include "functions.h"

int main(){

    playerInfo();
    readPlayersInformation();
    runGenerations(info.numGenerations);
    endGame();
}

//TODO

//add comments
//clean up code
// clean up .h file
// ask joshi is pointer passing is correct
// implemnet pointer arithmentic
// print with pointer arith

// memory leak detectoin 