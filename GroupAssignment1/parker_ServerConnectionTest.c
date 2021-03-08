#include "header.h"
#include <sys/socket.h>
#include <netinet/in.h>
int inet_addr();

int main()
{
    int entrySocket, connectionSocket; // socket file descriptors
    int bindCheck;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    // The three arguments are: Internet domain, Stream socket, Default protocol (TCP in this case)
    entrySocket = socket(PF_INET, SOCK_STREAM, 0); // Create the socket

    // Configure settings of the server address struct
    serverAddr.sin_family = AF_INET; //Address family = Internet
    serverAddr.sin_port = htons(7891); //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Set IP address to localhost
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    bindCheck = bind(entrySocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)); //Bind the address struct to the socket
    if (bindCheck < 0)
    {
        perror("[-]Error in bind");
        exit(1);
    }
    printf("[+]Binding successfull.\n");

    // Listen on the socket, with 5 max connection requests queued
    if (listen(entrySocket, 5) == 0) 
    {
        printf("[+]Listening....\n");
    }
    else 
    {
        printf("[-]Error in listening");
    }

    // Accept call creates a new socket for the incoming connection
    addr_size = sizeof serverStorage;
    connectionSocket = accept(entrySocket, (struct sockaddr *)&serverStorage, &addr_size);

    // SENDING AND RECEIVING AFTER THIS POINT
    //=======================================

    char buffer[3][1024];

    recv(connectionSocket, buffer[0], EMPLOYEENAME_LEN, 0); //Read the message from the server into the buffer
    recv(connectionSocket, buffer[1], JOBTITLE_LEN, 0); //Read the message from the server into the buffer
    recv(connectionSocket, buffer[2], STATUS_LEN, 0); //Read the message from the server into the buffer

    printf("[+]Data received:\n%s\n%s\n%s\n", buffer[0], buffer[1], buffer[2]); //Print the received message

    return 0;
}