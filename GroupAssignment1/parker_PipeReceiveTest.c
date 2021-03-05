
#include <stdio.h>     // Baisc standard I/O like printf
#include <string.h>    // required for strlen
#include <unistd.h>    // defines standard symbolic constants and types
#include <sys/types.h> // basic derived types like pid_t
#include <sys/stat.h>  //required for mkfifo (i.e. defines data returned by the stat() function: get file status)
#include <fcntl.h>     //required for open (i.e. file control options)

struct Test
{
    int age;
    char name[30];
};

void pipeReceive()
{
    int fd; // file descriptor

    struct Test received;
    struct Test *receivedPtr = &received;

    char myPipe[] = "./NamedPipe"; // FIFO file path
    mkfifo(myPipe, 0666);          // Creating the named file(FIFO)

    if ((fd = open(myPipe, O_RDONLY)) < 0) // Open FIFO for Read only
        printf("2: Error opening..");

    if (read(fd, receivedPtr, sizeof(receivedPtr) * 2) < 0) // Read from FIFO
        printf("2: Error reading..");

    // Display the results
    printf("Age: %d Name: %s\n", receivedPtr->age, receivedPtr->name); // Print the read message

    close(fd); // Close the pipe
}

int main()
{
    pipeReceive();
    return 0;
}