// Author: Dr. Shital Joshi
// Email: shital.joshi@okstate.edu
// Description: POSIX Interprocess communication using message queue

// Run: Use gcc add_messagePassing.c -lrt

#include <stdio.h>		// for printf
#include <time.h>		// for clock()
#include <unistd.h>		// for fork
#include <stdlib.h>		// for exit(1)
#include <sys/ipc.h> 	// Used by IPC maechanisms: messages, shared memory and semaphores
#include <sys/msg.h>	// for message queue structures
#include <string.h>		// for string operation: strlen
#include<sys/wait.h>	// for wait
#include <sys/fcntl.h>		// for file control options
#include <errno.h>		// for system error numbers
#include <mqueue.h>		// for mq_close, mq_unlink, ...

#define QUEUE_NAME   "/addition"
#define PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10


int main() 
{ 
	mqd_t qd;   // queue descriptors

	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MESSAGES;	// The maximum number of messages that can be stored on the queue. 
	attr.mq_msgsize = MAX_MSG_SIZE;	// The maximum size of each message on the given message queue. 
	attr.mq_curmsgs = 0;	// This field represents the number of messages currently on the given queue.


    int pid = fork();	// make two processes

	if (pid < 0){	// fork failed
		fprintf(stderr, "fork failed..\n");
		exit(1);
	}
    
    // Child process
	else if(pid == 0){ 
		if (mq_close (qd) == -1) {
		}

		if (mq_unlink (QUEUE_NAME) == -1) {
		}


		if ((qd = mq_open (QUEUE_NAME, O_WRONLY | O_CREAT, PERMISSIONS, &attr)) == -1) {
			perror ("Child: mq_open");
			exit (1);
		}

        int array[] = {5, 3, 27, 6, 99};
		char out_buffer [MAX_MSG_SIZE];

        int i;
        for (int i = 0; i < 5; i++){

            out_buffer[i] = array[i];
            setvbuf (stdout, NULL, _IONBF, 0);
            printf("%d\n", (int)out_buffer[i]);

            // sprintf((char)out_buffer[i], "%c", (char)array[i]);
        }
		
		if (mq_send (qd, out_buffer, strlen (out_buffer) + 1, 0) == -1) {
			perror ("Child: Not able to send message to the parent process..");
			exit(1);
		}

        printf("Sent!\n");
	}
    // Parent process
	else{	
		
		wait(NULL);		
		if ((qd = mq_open (QUEUE_NAME, O_RDONLY)) == -1) {
			perror ("Parent: mq_open");
			exit (1);
		}

		char in_buffer [MSG_BUFFER_SIZE];

		if (mq_receive (qd, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
			perror ("Parent: mq_receive");
			exit (1);
		}

        for (int i = 0; i < 5; i++){

		    printf ("Parent: Result received from child: %d\n\n", in_buffer[i]);


        }

		if (mq_close (qd) == -1) {
			perror ("Parent: mq_close");
			exit (1);
		}

		if (mq_unlink (QUEUE_NAME) == -1) {
			perror ("Parent: mq_unlink");
			exit (1);
		}
		
		exit(0);
	}
    			
	return 0; 
} 