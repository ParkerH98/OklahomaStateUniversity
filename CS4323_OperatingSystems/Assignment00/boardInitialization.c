// header file containing program function definitions and library imports
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#define WIDTH  100
#define HEIGHT 100


void readFile1(){

    FILE* f;
    int height, width, i, j;
    char gameBoard[HEIGHT][WIDTH];

    f = fopen("state.txt", "r");

    fscanf(f, "%d%d", &height, &width);


    for(i = 0; i < height; i++){

        for (j = 0; j < (width * 2) + 2; j++){

            fscanf(f, "%c", &gameBoard[j][i]);
        }
    }
    fclose(f);
    
    for(i = 0; i < height; i++){ 

        for(j = 0; j < (width * 2) + 2; j++){

            printf ("%c", gameBoard[j][i]);
        }

        printf("\n");
    }
}



void readFile(){

    /* Pointer to the file */
    FILE *fp;

    /* Character variable to read the content of file */
    char c;

    /* Opening a file in r mode*/
    fp = fopen ("state.txt", "r");

    /* Infinite loop –I have used break to come out of the loop*/
    while(1){

        c = fgetc(fp);

        if(c==EOF) break;

        else printf("%c", c);
    }
    fclose(fp);
}



void boardInitialization(){

}