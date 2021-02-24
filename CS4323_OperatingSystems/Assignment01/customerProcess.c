#include "header.h"

void customerProcess(mqd_t queueDescriptor, int numCustomers, int letter, int numItems, char order[], int *count, int zeroToHund[]){


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