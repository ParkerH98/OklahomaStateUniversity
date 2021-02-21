#include "header.h"


void helperOrder();
int getRandom();

void test(struct Item *perm){


    int numCustomers;
    int numItems;

    int letter = 64; // root parent gets the letter '@'

    char order[36];

    printf("How many Customer processes would you like?\n");
    scanf("%d", &numCustomers);

    // printf("Please specify a customer order.\n");
    // scanf("%s", order);

    pid_t pid = fork();

    // "Helper" process will execute
    if (pid == 0){

		helperOrder(NULL);
	}
    else if (pid > 0){

        int i = 0;

        while (i < numCustomers && pid > 0){

            printf("Customer%d with letter %c.\n\n", pid, letter);

            pid = fork();

            letter++;
            i++;
        }
    }



	// "Customer" processes will execute
	if (pid == 0){

        // printf("%d has letter %c\n", getpid(), letter);

		printf("Customer %c wants to know how many items you want.\n", letter);
		scanf("%d", &numItems);

        int i, randomItem;

        int itemsToGet[100];

        for (i = 0; i < numItems; i++)
        {

            randomItem = getRandom(getpid() * time(NULL));

            itemsToGet[i] = randomItem;

            // printf("Cust: %c is getting item %d\n", letter, randomItem);
        }

        // helperOrder(itemsToGet);

        printf("Customer %c is getting items ", letter);
        for (int i = 0; i < numItems; i++)
        {
            printf("%d ", itemsToGet[i]);
        }
        printf("\n");
    }

    // "Server" process will execute this 
	if (pid > 0){

        // printf("BITCHES\n");
    }


	while (wait(NULL) != -1 || errno != ECHILD){};


    
}


void helperOrder(int itemsToGet[]){







	exit(0);


}


void cust(){

}


int getRandom(int pid){

    int lower = 1, upper = 100;

    srand(pid);

    // sleep(1);

    int num = (rand() % (upper - lower + 1)) + lower;

    return num;
}