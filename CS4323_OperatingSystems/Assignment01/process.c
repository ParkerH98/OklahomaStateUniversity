#include "header.h"

void helperProcess(mqd_t qd);
void customerProcess(int letter, int msgID);
int getRandom();
void recMsg(int msgID);


#define QUEUE_NAME   "/addition"
#define PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10








void test(struct Item *perm){

    mqd_t qd;   // queue descriptors

	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MESSAGES;	// The maximum number of messages that can be stored on the queue. 
	attr.mq_msgsize = MAX_MSG_SIZE;	// The maximum size of each message on the given message queue. 
	attr.mq_curmsgs = 0;	// This field represents the number of messages currently on the given queue.




    int numItems;
    int letter = 64; // root parent gets the letter '@'

    int numCustomers;
    printf("How many Customer processes would you like?\n");
    scanf("%d", &numCustomers);

    char order[100];
    printf("Please specify a customer order.\n");
    scanf("%s", order);

    pid_t pid = fork();

    // "Helper" process will execute
    if (pid == 0){

		helperProcess(qd);
	}

    else if (pid > 0){

        int i = 0;

        while (i < numCustomers && pid > 0){

            pid = fork();
            letter++;
            i++;
        }
    }


    // "Customer" processes will execute
    if (pid == 0){

        
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

	while (wait(NULL) != -1 || errno != ECHILD){};
}

void helperProcess(mqd_t qd){



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

void customerProcess(int letter, int msgID){


    // printf("Customer %c wants to know how many items you want.\n", letter);
    // scanf("%d", &numItems);

    // int i, randomItem;

    // int itemsToGet[100];

    // for (i = 0; i < numItems; i++)
    // {

    //     randomItem = getRandom(getpid());

    //     itemsToGet[i] = randomItem;
    // }


}


void recMsg(int msgID){


}



int getRandom(int pid){

    int lower = 1, upper = 100;

    srand(pid * time(0));

    sleep(1);

    int num = (rand() % (upper - lower + 1)) + lower;

    return num;
}


// printf("Customer %c is getting items ", letter);
// for (int i = 0; i < numItems; i++)
// {
//     printf("%d ", itemsToGet[i]);
// }
// printf("\n");


// char *shm_order = mmap(NULL, sizeof(char) * 100,
// PROT_READ | PROT_WRITE,
// MAP_SHARED | MAP_ANONYMOUS, -1, 0);


//     for (int i = 0; i < 100; i++){

//     /* Read from the mapped/shared memory region */
//     printf ("%d %s %s %s\n", perm->serialNum, perm->item, perm->price, perm->store);
//     perm++;
//   }