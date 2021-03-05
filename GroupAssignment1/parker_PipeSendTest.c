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

void pipeSend()
{
    int fd; // file descriptor

    struct Test test;
    struct Test *testPtr = &test;

    testPtr->age = 22;
    strcpy(testPtr->name, "Parker Hague");

    printf("age: %d\n", testPtr -> age);
    printf("name: %s\n", testPtr -> name );

    char myPipe[] = "./NamedPipe"; // FIFO file path
    mkfifo(myPipe, 0666);          // Creating the named file(FIFO)

    if ((fd = open(myPipe, O_WRONLY | O_CREAT)) < 0) // Open FIFO for write only
        printf("1: Error opening..");

    if (write(fd, testPtr, sizeof(test) * 2) < 0) // Write on the FIFO
        printf("1: Error writing..");

    close(fd); // Close the pipe
}

int main()
{
    pipeSend();
    return 0;
}