#include "header.h"

void helperProcess(mqd_t queueDescriptor, struct mq_attr attr, int numCustomers, char order[]);
void customerProcess(int letter, int msgID);
int getRandom();
void shuffle(int *arr, size_t n);

char * receiveMessage(mqd_t msgID);

#define QUEUE_NAME   "/addition"
#define PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 1024
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

void test(struct Item *perm){

    int *count = mmap (NULL, sizeof (int),
    PROT_READ | PROT_WRITE,
    MAP_SHARED, -1, 0);

    mqd_t queueDescriptor;   // queue descriptors

	struct mq_attr attr;
	attr.mq_flags =IPC_NOWAIT;
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

    

    if ((queueDescriptor = mq_open (QUEUE_NAME, O_RDWR | O_CREAT, PERMISSIONS, &attr)) == -1) {
        perror ("Child: mq_open");
        exit (1);
    }

    pid_t pid = fork();

    // "Helper" process will execute
    if (pid == 0){

		helperProcess(queueDescriptor, attr, numCustomers, order);
	}

    else if (pid > 0){

        int i = 0;

        while (i < numCustomers && pid > 0){

            pid = fork();
            if(pid > 0) wait(NULL);
            // letter = order[letterCount];
            letter++;
            i++;
        }
    }

    // "Customer" processes will execute
    if (pid == 0){

        int priority;
        for (int i = 0; i < numCustomers; i++){

            if (letter == order[i]){
                priority = 100 - i;
            }
        }

        printf("Customer %c wants to know how many items you want.\n", letter);
        scanf("%d", &numItems);

        int i, randomItem;
        int itemsToGet[100];

        printf("Customer %c has\n", letter);
        for (i = 0; i < numItems; i++){

            randomItem = getRandom(getpid() + i);
            itemsToGet[i] = randomItem;
            printf("%d ", itemsToGet[i]);
        }

        printf("\n");

		if ((queueDescriptor = mq_open (QUEUE_NAME, O_WRONLY | O_CREAT, PERMISSIONS, &attr)) == -1) {
			perror ("Child: mq_open");
			exit (1);
		}

		char out_buffer [numItems];

        for (int i = 0; i < numItems; i++){

            out_buffer[i] = itemsToGet[i];
        }

        if (mq_send (queueDescriptor, out_buffer, strlen (out_buffer) + 1, priority) == -1) {
            perror ("Child: Not able to send message to the parent process..");
            exit(1);
        }
        printf("Sent!\n");
    }
}


void helperProcess(mqd_t queueDescriptor, struct mq_attr attr, int numCustomers, char order[]){

    sleep(3);

    for (int i = 0; i < numCustomers; i++){

        char *in = receiveMessage(queueDescriptor);

        for (int i = 0; i < 5; i++){

           printf ("Helper: Received from Customer: %d\n\n", in[i]);
        }
    }

    if (mq_close (queueDescriptor) == -1) {
        perror ("Parent: mq_close");
        exit (1);
    }

    if (mq_unlink (QUEUE_NAME) == -1) {
        perror ("Parent: mq_unlink");
        exit (1);
    }
            
    exit(0);
}

char * receiveMessage(mqd_t msgID){

    char in_buffer [MSG_BUFFER_SIZE];
    char *s = malloc(sizeof(char) * 5);

    printf("About to recieve\n");

    if (mq_receive (msgID, in_buffer, MSG_BUFFER_SIZE, 0) == -1) {
        perror ("Parent: mq_receive");
        exit (1);
    }

    for(int j = 0; j < 5; j++){
        s[j] = in_buffer[j];
    //    printf("%d\n", (int)s[j]);
    }
    
    return s;
}

int getRandom(int pid){

    int lower = 1, upper = 100;

    srand(pid * time(0));
    int num = (rand() % (upper - lower + 1)) + lower;

    return num;
}


//     int zeroToHund[100];

// for (i = 0; i < 100; i++){
//     zeroToHund[i] = i;
// }

// shuffle(zeroToHund, 100);

// for (i = 0; i < 100; i++){
//     printf("%d ", zeroToHund[i]);
// }

//     void shuffle(int *arr, size_t n)
// {
//     if (n > 1) 
//     {
//         size_t i;
//         srand(time(NULL));
//         for (i = 0; i < n - 1; i++) 
//         {
//           size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
//           int t = arr[j];
//           arr[j] = arr[i];
//           arr[i] = t;
//         }
//     }
// }
