#include "header.h"
#include <sys/socket.h>
#include <netinet/in.h>
int inet_addr();

int main()
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size; 

    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");

    // Configure settings of the server address struct
    serverAddr.sin_family = AF_INET; //Address family = Internet
    serverAddr.sin_port = htons(7891); //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Set IP address to localhost
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    // Connect the socket to the server using the address struct
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *)&serverAddr, addr_size);
    if (clientSocket == -1)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Connected to Server.\n");

    // SENDING AND RECEIVING AFTER THIS POINT
    //=======================================

    struct Query query;
    struct Query *queryPtr = &query;

    strcpy(queryPtr->employeeName, "Parker Hague");
    strcpy(queryPtr->jobTitle, "International Programmer");
    strcpy(queryPtr->status, "FT");

    send(clientSocket, queryPtr->employeeName, EMPLOYEENAME_LEN, 0);
    send(clientSocket, queryPtr->jobTitle, JOBTITLE_LEN, 0);
    send(clientSocket, queryPtr->status, STATUS_LEN, 0);

    printf("[+]Data sent successfully.\n");

    printf("[+]Closing the connection.\n");

    close(clientSocket);

    return 0;
}