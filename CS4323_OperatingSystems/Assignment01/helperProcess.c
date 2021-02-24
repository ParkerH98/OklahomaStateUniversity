#include "header.h"
char *receiveMessage(mqd_t queueDescriptor);
/*
---------------------------------------------------------
Function is executed by the Helper process. This process is
responsible for handling the receiving end of the message 
queue. After the Helper receives the list of serial numbers, 
the Helper then writes the items to an ouput file.

Params: the message queue descriptor, message queue struct attributes, the number of Customer processes, a char array of the Customer order, and a shared memory struct Item array
Return: void
*/
void helperProcess(mqd_t queueDescriptor, struct mq_attr attr, int numCustomers, char order[], struct Item *shm_struct)
{
    sleep(5); // helps to control the flow and timing of the program

    float total = 0; // stores total for each Customer
    int letter = 0; // stores each Customer's letter

    int numItems; // stores the number of items for a particular Customer

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


/*
---------------------------------------------------------
Function handles receiving the main output buffer message 
in the message queue from the Customer process. Function is
called in the helperProcess function.

Params: the message queue descriptor
Return: a char pointer to the received output message buffer
*/
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