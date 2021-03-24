#include "header.h"

/*
---------------------------------------------------------
IPC send function via named pipe. Pipe sends user query
from the Manager process to the Assistant process.

Params: pointers to the employee name, job title, and status of the query
Return: void
*/
void pipeSend(char *employeeName, char *jobTitle, char *status)
{
    int fd; // file descriptor

    struct Query send; // struct to hold query
    struct Query *sendPtr = &send; // pointer to query

    strcpy(sendPtr->employeeName, employeeName); // copies input parameters to the struct to be sent
    strcpy(sendPtr->jobTitle, jobTitle);
    strcpy(sendPtr->status, status); 

    // debug print -- remove later
    // printf("\nSENT TO ASSISTANT VIA PIPE:\nEmployee Name: %s\nJob Title: %s\nStatus: %s\n\n", sendPtr->employeeName, sendPtr->jobTitle, sendPtr->status); // Print the read message

    char myPipe[] = "./NamedPipe2"; // FIFO file path
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

/*
---------------------------------------------------------
IPC receive function via named pipe. Pipe receives user query
from the Manager process to the Assistant process.

Params: none
Return: an instance of the Query struct containing the user query information
*/
struct Query pipeReceive()
{
    int fd; // file descriptor

    struct Query received; // holds received user query information
    struct Query *receivedPtr = &received; // pointer to the received query

    char myPipe[] = "./NamedPipe2"; // FIFO file path
    mkfifo(myPipe, 0666);          // Creating the named file(FIFO)

    if ((fd = open(myPipe, O_RDONLY)) < 0) // Open FIFO for Read only
    {
        printf("2: Error opening..");
    }

    if (read(fd, receivedPtr, sizeof(struct Query)) < 0) // Read from FIFO
    {
        printf("2: Error reading..");
    }

    // debug print -- remove later
    // printf("\nRECEIVED:\nEmployee Name: %s\n Job Title: %s\n Status: %s\n", receivedPtr->employeeName, receivedPtr->jobTitle, receivedPtr->status); // Print the read message

    close(fd); // Close the pipe
    return received;
}