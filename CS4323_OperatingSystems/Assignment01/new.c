#include <stdio.h>		// for printf
#include <time.h>		// for clock()
#include <unistd.h>		// for fork
#include <stdlib.h>		// for exit(1)
#include <sys/ipc.h> 	// Used by IPC maechanisms: messages, shared memory and semaphores
#include <string.h>		// for string operation: strlen
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <assert.h>






int main(){

//       // struct to hold player information
// struct Item{
//     int serialNum;
//     char item[256];
//     char price[16];
//     char store[64];
// };





//     int shmfd = shm_open ("/OpenCSF_SHM", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);

//     /* Resize the region to store 1 struct instance */
//     ftruncate (shmfd, sizeof (struct Item));

//     /* Map the object into memory so file operations aren't needed */
//     struct Item *ptr = mmap (NULL, sizeof (struct Item),
//                                     PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);

//       /* Create a child process and write to the mapped/shared region */
//     pid_t child_pid = fork();
//     if (child_pid == 0)
//     {
//         ptr->serialNum = 6;

//         strcpy(ptr->item, "toilet");
//         strcpy(ptr->price, "$89.00");
//         strcpy(ptr->store, "Amazon");


//         /* Unmap and close the child's shared memory access */
//         munmap (ptr, sizeof (struct Item));
//         close (shmfd);
//         return 0;
//     }

//     /* Make the parent wait until the child has exited */
//     wait (NULL);

//     /* Read from the mapped/shared memory region */
//     printf ("Permission bit-mask: %d %s %s %s\n", ptr->serialNum, ptr->item, ptr->price, ptr->store);

//     /* Unmap, close, and delete the shared memory object */
//     munmap (ptr, sizeof (struct Item));
//     close (shmfd);
//     shm_unlink ("/OpenCSF_SHM");



struct Item {
  int serialNum;
    char item[256];
    char price[16];
    char store[64];
};



    int shmfd = shm_open ("test", O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
assert (shmfd != -1);

/* Resize the region to store 1 struct instance */
assert (ftruncate (shmfd, sizeof (struct Item)) != -1);

/* Map the object into memory so file operations aren't needed */
struct Item *perm = mmap (NULL, sizeof (struct Item),
                                PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
assert (perm != MAP_FAILED);

/* Create a child process and write to the mapped/shared region */
pid_t child_pid = fork();
if (child_pid == 0)
  {
    perm->serialNum = 6;

    strcpy(perm->item, "hello");
    strcpy(perm->store, "dog");
    strcpy(perm->price, "cat");


    /* Unmap and close the child's shared memory access */
    munmap (perm, sizeof (struct Item));
    close (shmfd);
    return 0;
  }

/* Make the parent wait until the child has exited */
wait (NULL);

/* Read from the mapped/shared memory region */
printf ("Permission bit-mask: 0%d %s %s %s\n", perm->serialNum, perm->item, perm->store, perm->price);

/* Unmap, close, and delete the shared memory object */
munmap (perm, sizeof (struct Item));
close (shmfd);
shm_unlink ("test");

    
}