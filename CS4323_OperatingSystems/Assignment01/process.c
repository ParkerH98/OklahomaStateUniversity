#include "header.h"

void helperProcess(int msgID, char order[]);
void customerProcess(int letter, int msgID);
int getRandom();
void recMsg(int msgID);









void test(struct Item *perm){

   




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

		// helperProcess(msgID, order);
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






    }

	while (wait(NULL) != -1 || errno != ECHILD){};
}

void helperProcess(int msgID, char order[]){


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

    struct Message sender;
    sender.messageType = letter;
    strcpy(sender.message, "HEllO");

    // msgsnd to send message
    if (msgsnd(msgID, &sender, sizeof(sender.message), 0) == -1)
    {
        perror("msgsnd");
        exit(1);
    }

    // display the message
    printf("Data send is : %s \n", sender.message);
}


void recMsg(int msgID){

    int i;

    while (1){

        struct Message receiver;

        if((msgrcv(msgID, &receiver, sizeof(receiver), 1, 0)) == -1){
            perror("msgrcv");
            exit(1);
        }
        printf("\nI got: %s", receiver.message);

        if(msgctl(msgID, IPC_RMID, NULL) == -1){
            perror("msgctl");
        }
    }
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