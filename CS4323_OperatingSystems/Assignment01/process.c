#include "header.h"
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/shm.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <sys/mman.h>




void test(){




    /* the size (in bytes) of shared memory object */
    const int SIZE = 4096; 
  
    /* name of the shared memory object */
    const char* name = "items.txt"; 
  
    /* shared memory file descriptor */
    int shm_fd; 
  
    /* pointer to shared memory object */
    void* ptr; 
  
    /* open the shared memory object */
    shm_fd = shm_open(name, O_CREAT, 0666); 
  
    /* memory map the shared memory object */
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0); 
  
    /* read from the shared memory object */
    printf("%s", (char*)ptr); 
  
    /* remove the shared memory object */
    shm_unlink(name);


    int numCustomers;
    int numItems;

    printf("How many Customer processes would you like?\n");
    scanf("%d", &numCustomers);


    // loop will run n times
    for(int i = 0; i < numCustomers; i++){ 

        // IS child process
        if(fork() == 0){

            printf("Customer%d wants to know how many items you'd like.\n", getpid());
            scanf("%d", &numItems);









            // printf("[son] pid %d from [parent] pid %d\n", getpid(), getppid());
            exit(0); 
        } 
    } 
    for(int i = 0; i < numCustomers; i++) // loop will run n times (n=5) 
    wait(NULL);

}