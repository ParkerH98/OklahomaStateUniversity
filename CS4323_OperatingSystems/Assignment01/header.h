#include <ctype.h>      // used for a string manipulation
#include <stdio.h>		// for printf
#include <time.h>		// for clock()
#include <unistd.h>		// for fork
#include <stdlib.h>		// for exit(1)
#include <sys/ipc.h> 	// Used by IPC maechanisms: messages, shared memory and semaphores
#include <string.h>		// for string operation: strlen
#include <sys/msg.h>	// for message queue structures
#include<sys/wait.h>	// for wait
#include <sys/fcntl.h>		// for file control options
#include <errno.h>		// for system error numbers
#include <mqueue.h>		// for mq_close, mq_unlink, ...
#include <sys/shm.h>    
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h> 
#include <assert.h>     // used to throw error for shared memory

#define NUM_ITEMS 100   // number of items in items.txt
#define QUEUE_NAME "/addition"
#define PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 1024
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

// struct to hold player information
struct Item{
    int serialNum;
    char item[256];
    char price[16];
    char store[64];
};

// function prototypes for functions used in external .c files
void readFile();
void process(struct Item *shm_struct);
void removeFirst(char * str, const char toRemove);
char *trim(char *str);
void helperProcess(mqd_t queueDescriptor, struct mq_attr attr, int numCustomers, char order[], struct Item *shm_struct);
void customerProcess(mqd_t queueDescriptor, int numCustomers, int letter, int numItems, char order[], int *count, int zeroToHund[]);