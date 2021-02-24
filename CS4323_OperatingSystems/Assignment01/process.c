// will change defines on ubuntu
// will change prototypes on ubuntu
// free memory
// delete random


#include "header.h"

void helperProcess(mqd_t queueDescriptor, struct mq_attr attr, int numCustomers, char order[], struct Item *shm_struct);
void customerProcess(int letter, int msgID);
int getRandom();
void shuffleArray(int *arr, size_t n);

char *receiveMessage(mqd_t msgID);

#define QUEUE_NAME "/addition"
#define PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 1024
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10


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
        int priority; // priority used for message queue to specify order
        for (int i = 0; i < numCustomers; i++)
        {
            if (letter == order[i]){ // assigns a priority based on the entered order -- priority starts at 100 and decrements
                priority = 100 - i;
            }
        }

        int remainingItems = *count; // keeps track of the amount of available items remaining

        printf("Customer %c wants to know how many items you want. Remaining: %d\n", letter, 100 - remainingItems);
        scanf("%d", &numItems); // stores number of requested items per each Customer process

        int i, randomItem; // will hold the serialNumber of the randomly selected item
        int itemsToGet[101]; // array to store each Customer process's item -- added 1 because the first index holds the number of items

        itemsToGet[0] = numItems; // stores the number of items in the first index to send to the helper via message queue

        printf("Cust:(%c) (%d) has %d items --> ", letter, getpid(), itemsToGet[0]);
        for (i = 0; i < numItems; i++)
        {
            randomItem = zeroToHund[*count]; // selects the random item from the array based on the shared memory count variable
            itemsToGet[i + 1] = randomItem; // stores the random item serial number into the items array

            printf("%d ", itemsToGet[i + 1]); // prints the Customers items that they're going to get

            *count = *count + 1; // increments the shared memory count -- this is done to avoid duplicate items
        }

        char out_buffer[numItems]; // output buffer that is going to be sent to the message queue

        for (int i = 0; i < numItems; i++)
        {
            out_buffer[i] = itemsToGet[i]; // assigns the requested items serial numbers to the output buffer
        }

        char out_pid[20]; // char array to store the Customer PID
        sprintf(out_pid, "%d", getpid()); // writes the PID to the char array

        if (mq_send(queueDescriptor, out_pid, strlen(out_buffer) + 1, priority) == -1){ // message queue send function to send the Customer PID
            perror("Child: Not able to send message to the parent process..");
            exit(1);
        }

        if (mq_send(queueDescriptor, out_buffer, strlen(out_buffer) + 1, priority) == -1){ // message queue send function to output buffer containing the item serial numbers
            perror("Child: Not able to send message to the parent process..");
            exit(1);
        }
        printf("Sent!\n");
        printf("---------------------------------------------\n\n");
    }
}

void helperProcess(mqd_t queueDescriptor, struct mq_attr attr, int numCustomers, char order[], struct Item *shm_struct)
{
    sleep(3); // helps to control the flow and timing of the program

    float total = 0; // stores total for each Customer
    int letter = 0; // stores each Customer's letter

    int numItems; // stores the number of items for a particular Customer




    int pid; // stores the PID for a particular Customer




    char filename[17] = "processReceipt"; // output filename

    for (int i = 0; i < numCustomers; i++) // loops once per each Customer
    {
        filename[14] = order[i]; // appends the Cutomer letter to the filename

        FILE *f; // file pointer

        f = fopen(filename, "w+"); // opens the file with read/write privileges

        char in_pid[10]; // stores Customer PID

        if (mq_receive(queueDescriptor, in_pid, MSG_BUFFER_SIZE, 0) == -1) // message queue receive function to get the Customer PID from the sender
        {
            perror("Parent: mq_receive");
            exit(1);
        }

        char *in = receiveMessage(queueDescriptor); // receives output buffer message and stores into variable in

        total = 0; // reinitializes the total for each Customer
        numItems = in[0]; // assigns number of items to the first index sent from the Customer via message queue

        fprintf(f, "Customer (%c) (%s) has items:\n\n", order[letter], in_pid); // prints header to file

        for (int i = 0; i < numItems; i++) // loops once for each item per Customer
        {
            removeFirst(shm_struct[in[i]].price, '$'); // removes the '$' from the struct arrau price passed via the shared memory
            total = total + atof(shm_struct[in[i]].price); // calculates total and converts to float

            fprintf(f, "%s          $%s at %s\n", shm_struct[in[i]].item, shm_struct[in[i]].price, shm_struct[in[i]].store); // prints each item to file
        }
        fprintf(f, "\n");
        fprintf(f, "Total: $%.2f\n\n", total); // prints total to bottom of file
        fprintf(f, "\n");

        letter = letter + 1; // increments the Customer letter
        fclose(f); // closes the file
    }

    if (mq_close(queueDescriptor) == -1){ // closes the message queue
        perror("Parent: mq_close");
        exit(1);
    }

    if (mq_unlink(QUEUE_NAME) == -1){ // deletes the message queue
        perror("Parent: mq_unlink");
        exit(1);
    }

    exit(0); // Helper process exits
}

char *receiveMessage(mqd_t queueDescriptor)
{
    char in_buffer[MSG_BUFFER_SIZE]; // stores message sent in message queue

    if (mq_receive(queueDescriptor, in_buffer, MSG_BUFFER_SIZE, 0) == -1) // message queue receive function to get the output buffer from the sender
    {
        perror("Parent: mq_receive");
        exit(1);
    }

    int numItems = in_buffer[0]; // gets number of items from first element in message

    char *s = malloc(sizeof(char) * numItems); // allocates size array to hold the message

    for (int i = 0; i < numItems; i++) // assigns the dynamically allocated array to hold the contents of the output buffer message
    {
        s[i] = in_buffer[i];
    }
    return s;
}

int getRandom(int pid)
{
    int lower = 1, upper = 99;

    srand(pid * time(0));
    int num = (rand() % (upper - lower + 1)) + lower;

    return num;
}

/*
---------------------------------------------------------
Function takes in input array and shuffles the contents
of the array. This is used to get non duplicated random
numbers for the item lists.

Params: int array to be shuffled and n number of elements in array
Return: void
*/
void shuffleArray(int *arrayToShuffle, int n)
{
    if (n > 1)
    {
        int i;
        srand(time(NULL)); // sets seed for random
        for (i = 0; i < n - 1; i++)
        {
            int j = i + rand() / (RAND_MAX / (n - i) + 1); // gets random element in range
            int temp = arrayToShuffle[j];
            arrayToShuffle[j] = arrayToShuffle[i]; // swaps indices
            arrayToShuffle[i] = temp; // assigns to temp index
        }
    }
}