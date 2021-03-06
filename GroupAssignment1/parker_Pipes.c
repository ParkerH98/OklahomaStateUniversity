#include "header.h"

void pipeSend(char *employeeName, char *jobTitle, char *status)
{
    int fd; // file descriptor

    struct Query send;
    struct Query *sendPtr = &send;

    strcpy(sendPtr->employeeName, employeeName);
    strcpy(sendPtr->jobTitle, jobTitle);
    strcpy(sendPtr->status, status);

    printf("SENT:\nEmployee Name: %s\nJob Title: %s\nStatus: %s\n\n", sendPtr->employeeName, sendPtr->jobTitle, sendPtr->status); // Print the read message

    char myPipe[] = "./NamedPipe"; // FIFO file path
    mkfifo(myPipe, 0666);          // Creating the named file(FIFO)

    if ((fd = open(myPipe, O_WRONLY | O_CREAT)) < 0) // Open FIFO for write only
    {
        printf("1: Error opening..");
    }

    if (write(fd, sendPtr, sizeof(struct Query)) < 0) // Write on the FIFO
    {
        printf("1: Error writing..");
    }

    close(fd); // Close the pipe
}

struct Query pipeReceive()
{
    int fd; // file descriptor

    struct Query received;
    struct Query *receivedPtr = &received;

    char myPipe[] = "./NamedPipe"; // FIFO file path
    mkfifo(myPipe, 0666);          // Creating the named file(FIFO)

    if ((fd = open(myPipe, O_RDONLY)) < 0) // Open FIFO for Read only
    {
        printf("2: Error opening..");
    }

    if (read(fd, receivedPtr, sizeof(struct Query)) < 0) // Read from FIFO
    {
        printf("2: Error reading..");
    }

    // Display the results
    // printf("\nRECEIVED:\nEmployee Name: %s\n Job Title: %s\n Status: %s\n", receivedPtr->employeeName, receivedPtr->jobTitle, receivedPtr->status); // Print the read message

    return received;



    close(fd); // Close the pipe
    // fclose(f);
}