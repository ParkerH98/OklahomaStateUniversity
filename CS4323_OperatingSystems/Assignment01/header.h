#include <ctype.h>
#include <stdio.h>		// for printf
#include <time.h>		// for clock()
#include <unistd.h>		// for fork
#include <stdlib.h>		// for exit(1)
#include <sys/ipc.h> 	// Used by IPC maechanisms: messages, shared memory and semaphores
#include <string.h>		// for string operation: strlen
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h> 
#include <errno.h>
#include <assert.h>
#include <time.h>


#define NUM_ITEMS 100

// struct to hold player information
struct Item{
    int serialNum;
    char item[256];
    char price[16];
    char store[64];
};


// extern struct Item itemsList[100];

void readFile();

void test(struct Item *perm);


