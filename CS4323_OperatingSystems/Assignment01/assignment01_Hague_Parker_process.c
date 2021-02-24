// free memory


#include "header.h"

// void customerProcess(mqd_t queueDescriptor, int numCustomers, int letter, int numItems, char order[], int *count, int zeroToHund[]);
void shuffleArray(int *arr, int n);

char *receiveMessage(mqd_t msgID);




/*
---------------------------------------------------------
Function creates child processes and uses shared memory to
pass information between Server and Customer processes. Then,
gets items and uses message queue to pass items to the Helper
where the helper then retrieves the items from the shared 
memory (shm_struct) and prints the items to output files.

Params: pointer to a shared memory struct
Return: void
*/
void process(struct Item *shm_struct)
{
    int *count = mmap(NULL, sizeof(int), // creates shared memory object for processes to keep track of current index in the zeroToHundo array
                      PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    mqd_t queueDescriptor; // queue descriptor

    struct mq_attr attr; // message queue attributes necessary for message queue functionality
    attr.mq_flags = IPC_NOWAIT;
    attr.mq_maxmsg = MAX_MESSAGES;  // The maximum number of messages that can be stored on the queue.
    attr.mq_msgsize = MAX_MSG_SIZE; // The maximum size of each message on the given message queue.
    attr.mq_curmsgs = 0;            // This field represents the number of messages currently on the given queue.

    if ((queueDescriptor = mq_open(QUEUE_NAME, O_RDWR | O_CREAT, PERMISSIONS, &attr)) == -1){ // opens a message queue
        perror("Child: mq_open");
        exit(1);
    }

    int numItems; // number of items each Customer process has
    int letter = 64; // root parent gets the letter '@' (so the child will start with A)

    int numCustomers; // gets and assigns number of Customer processes
    printf("How many Customer processes would you like?\n");
    scanf("%d", &numCustomers);

    char order[100]; // gets and assigns a specific customer order denoted by capital alphabetic letters
    printf("Please specify a customer order.\n");
    scanf("%s", order);

    int zeroToHund[100]; // array to hold numbers 1-100 for items assignment
    int i; // looping
    *count = 0; // initializes shared memory count to 0

    for (i = 0; i < 100; i++) // assigns numbers 1-100 to array
    {
        zeroToHund[i] = i;
    }

    shuffleArray(zeroToHund, 100); // randomly shuffles the zeroToHund array

    pid_t pid = fork(); // creates a child process

    if (pid == 0)   //"Helper" process will execute
    {
        helperProcess(queueDescriptor, attr, numCustomers, order, shm_struct); // executes Helper process code
    }

    else if (pid > 0) // parent will execute
    {
        int i = 0;

        while (i < numCustomers && pid > 0) // create the number of desired Customer processes
        {
            pid = fork(); // creates child

            if (pid > 0) // parent waits for child to finish executing
                wait(NULL);

            letter++; // increments the Customers letter -- it will go A, B, C, ..., Z
            i++;
        }
    }

    if (pid == 0)   // "Customer" processes will execute
    {
        customerProcess(queueDescriptor, numCustomers, letter, numItems, order, count, zeroToHund);
    }
}



/*
---------------------------------------------------------
Function takes in input array and shuffles the contents
of the array. This is used to get non duplicated random
numbers for the item lists.

Params: int array to be shuffled and n number of elements in array
Return: void
*/
void shuffleArray(int *arrayToShuffle, int numElements)
{
    if (numElements > 1)
    {
        int i;
        srand(time(NULL)); // sets seed for random
        for (i = 0; i < numElements - 1; i++)
        {
            int j = i + rand() / (RAND_MAX / (numElements - i) + 1); // gets random element in range
            int temp = arrayToShuffle[j];
            arrayToShuffle[j] = arrayToShuffle[i]; // swaps indices
            arrayToShuffle[i] = temp; // assigns to temp index
        }
    }
}