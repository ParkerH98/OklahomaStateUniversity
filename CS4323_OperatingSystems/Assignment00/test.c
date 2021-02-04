#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testArr(int (*ptr)[4]);


int main(){


    int arr[3][4] = {
    {11,22,33,44},
    {55,66,77,88},
    {11,66,77,44}
    };

    int (*ptr)[4];
    ptr = arr;

    testArr(ptr);
}


void testArr(int (*ptr)[4]){

    int i, j;

    for (i = 0; i < 3; i++)
    {
        // printf("Address of %d th array %u \n",i , *(ptr + i));
        for(j = 0; j < 4; j++)
        {
             printf("arr[%d][%d]=%d\n", i, j, *( *(ptr + i) + j) );
        }
        printf("\n\n");
    }

}