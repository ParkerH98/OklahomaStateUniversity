#include "header.h"


void helperOrder();


void test(struct Item *perm){


    int numCustomers;
    int numItems;

    int letter = 64; // root parent gets the letter '@'

    char order[36];

    printf("How many Customer processes would you like?\n");
    scanf("%d", &numCustomers);

    printf("Please specify a customer order.\n");
    scanf("%s", order);

    pid_t pid = fork();

    // "Helper" process will execute
    if (pid == 0){

		helperOrder();
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

		printf("Customer%d with letter %c wants to know how many items you want.\n", getpid(), letter);
		scanf("%d", &numItems);

        
	}

	// "Server" process will execute this 
	if (pid > 0){

        // printf("BITCHES\n");
    }


	while (wait(NULL) != -1 || errno != ECHILD){};


    
}


void helperOrder(){

	exit(0);


}


void cust(){

}