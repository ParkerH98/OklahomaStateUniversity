#include "header.h"
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <sys/mman.h>
#include <errno.h>


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

void helperOrder();

#define QUEUE_NAME   "/addition"
#define PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10
#define MAX 9000000000 // 9 billion times



// void test(){

// 	/* size (in bytes) of shared memory object */
// 	const int SIZE = 1024;
		
// 	/* name of the shared memory object */
// 	const char *name = "CS4323";
	
// 	/* shared memory file descriptor */
// 	int shm_fd;
		
// 	/* pointer to shared memory object */
// 	struct Item *ptr;
// 	struct Item itemsList;

// 	/* Create or open a shared memory object */
// 	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 

// 	/* Set the shared memory object size */
// 	ftruncate(shm_fd, SIZE);

// 	/* Map the shared memory object into the current address space */
// 	ptr = mmap(0, SIZE,  PROT_WRITE, MAP_SHARED, shm_fd, 0);

// 	for (int i = 0; i < 100; i++){
	
// 		/* Write to the shared memory object */
// 		ptr = &itemsList;
// 		ptr++;
// 	}

// 	pid_t pid = fork();

// 	if (pid > 0){
// 		printf("IM A APRNET");
// 	}

// 	if (pid == 0)
// 	{
// 		/* open the shared memory object */
// 		shm_fd = shm_open(name, O_RDONLY, 0666);

// 		wait(NULL);

// 		/* memory map the shared memory object */
// 		ptr = (struct Item *) mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

// 		// printf("IM A CHILD");

// 		printf("%s", (*ptr).item);
// 		// printf("PRINTED%d", *ptr);

// 		/* Unmap the shared memory */
// 		munmap(ptr, SIZE);
		
// 		/* Close the shared memory object */ 
// 		close(shm_fd);

// 		/* Delete the shared memory object */
// 		shm_unlink(name);
// 	}
// }




//     int numCustomers;
//     int numItems;

//     int letter = 64; // root parent gets the letter '@'

    // char order[36];

    // printf("How many Customer processes would you like?\n");
    // scanf("%d", &numCustomers);

    // printf("Please specify a customer order.\n");
    // scanf("%s", order);

//     pid_t pid = fork();

//     // "Helper" process will execute
//     if (pid == 0){

// 		helperOrder();
// 	}
//     else if (pid > 0){

//         int i = 0;

//         while (i < numCustomers && pid > 0){

//             printf("Customer%d with letter %c.\n\n", pid, letter);

//             pid = fork();

//             letter++;
//             i++;
//         }
//     }


// 	// "Customer" processes will execute
// 	if (pid == 0){

//         // printf("%d has letter %c\n", getpid(), letter);

// 		printf("Customer%d with letter %c wants to know how many items you want.\n", getpid(), letter);
// 		scanf("%d", &numItems);
// 	}

// 	// "Server" process will execute this 
// 	if (pid > 0){

//         printf("BITCHES\n");
//     }


// 	while (wait(NULL) != -1 || errno != ECHILD){};
// }


// void helperOrder(){

// 	exit(0);


// }


// void cust(){

// }