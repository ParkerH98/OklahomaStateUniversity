#include "header.h"


#define QUEUE_NAME "parker"
#define PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10



int main(){



    
}


void msgTest(){

    mqd_t qd;   // queue descriptors

	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;	// The maximum number of messages that can be stored on the queue. 
	attr.mq_msgsize = 256;	// The maximum size of each message on the given message queue. 
	attr.mq_curmsgs = 0;	// This field represents the number of messages currently on the given queue.

    int msgID = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);


    if ((qd = mq_open (QUEUE_NAME, O_WRONLY | O_CREAT, PERMISSIONS, &attr)) == -1) {
        perror ("Child: mq_open");
        exit (1);
    }


    int out_buffer [MSG_BUFFER_SIZE];


    sprintf (out_buffer, "%lld", 5);


    if (mq_send (qd, out_buffer, strlen (out_buffer) + 1, 0) == -1) {
        perror ("Child: Not able to send message to the parent process..");
        exit(1);
    }





}



void recTest(){

    if ((qd = mq_open (QUEUE_NAME, O_RDONLY)) == -1) {
        perror ("Parent: mq_open");
        exit (1);
    }

    char in_buffer [MSG_BUFFER_SIZE];

    if (mq_receive (qd, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
        perror ("Parent: mq_receive");
        exit (1);
    }
    printf ("Parent: Result received from child: %s\n\n", in_buffer);


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