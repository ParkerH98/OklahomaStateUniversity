#include "header.h"
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 9004


int inet_addr();

// =======================================================================
// CLIENT CONNECTION FUCNTIONS
// =======================================================================

void forwardQueryToServer(char *employeeName, char *jobTitle, char *status)
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    // 
 

    // The three arguments are: Internet domain, Stream socket, Default protocol (TCP in this case)
    clientSocket = socket(PF_INET, SOCK_STREAM, 0); // Create the socket
    if (clientSocket < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    // printf("[+]Server socket created successfully.\n");

    // Configure settings of the server address struct
    serverAddr.sin_family = AF_INET; //Address family = Internet
    serverAddr.sin_port = htons(PORT); //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //Set IP address to localhost
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    // Connect the socket to the server using the address struct
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *)&serverAddr, addr_size);
    if (clientSocket == -1)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    // printf("[+]Connected to Server.\n\n");

    // SENDING AND RECEIVING AFTER THIS POINT
    //=======================================

    struct Query query;
    struct Query *queryPtr = &query;

    // assigns input data to Query struct
    strcpy(queryPtr->employeeName, employeeName);
    strcpy(queryPtr->jobTitle, jobTitle);
    strcpy(queryPtr->status, status);

    send(clientSocket, queryPtr->employeeName, EMPLOYEENAME_LEN, 0);
    send(clientSocket, queryPtr->jobTitle, JOBTITLE_LEN, 0);
    send(clientSocket, queryPtr->status, STATUS_LEN, 0);

    printf("[+]Data sent successfully from assistant.\n");

    // printf("[+]Closing the connection.\n");

    close(clientSocket);
}


/*
---------------------------------------------------------
Creates a socket connection to the Server to receive the 
results from the previously forwarded query.

Params: none
Return: void
*/
void receiveResultFromServer()
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    // The three arguments are: Internet domain, Stream socket, Default protocol (TCP in this case)
    clientSocket = socket(PF_INET, SOCK_STREAM, 0); // Create the socket
    if (clientSocket < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    // printf("\n[+]Server socket created successfully.\n");

    // Configure settings of the server address struct
    serverAddr.sin_family = AF_INET;                               //Address family = Internet
    serverAddr.sin_port = htons(7892);                             //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");           //Set IP address to localhost
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    // Connect the socket to the server using the address struct
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *)&serverAddr, addr_size);
    if (clientSocket == -1)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    // printf("[+]Connected to Server.\n");

    // SENDING AND RECEIVING AFTER THIS POINT
    //=======================================

    char buffer[3][1024];

    recv(clientSocket, buffer[0], EMPLOYEENAME_LEN, 0); //Read the message from the server into the buffer
    recv(clientSocket, buffer[1], JOBTITLE_LEN, 0); //Read the message from the server into the buffer
    recv(clientSocket, buffer[2], STATUS_LEN, 0); //Read the message from the server into the buffer

    printf("[+]Data received from server:\n\n%s\n%s\n%s\n", buffer[0], buffer[1], buffer[2]); //Print the received message


    // printf("[+]Closing the connection.\n");

    close(clientSocket);
}






// =======================================================================
// SERVER CONNECTION FUCNTIONS
// =======================================================================
/*
---------------------------------------------------------
Listens for an incoming socket connection from the Assistant
and then sends the results from the query request back to the 
Assistant via the socket connection.

Params: none
Return: void
*/
void sendResultToAssistant() // SERVER
{

    struct Query
    {
        char employeeName[EMPLOYEENAME_LEN];
        char jobTitle[JOBTITLE_LEN];
        char status[STATUS_LEN];
    };

    int entrySocket, connectionSocket; // socket file descriptors
    int bindCheck;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    // The three arguments are: Internet domain, Stream socket, Default protocol (TCP in this case)
    entrySocket = socket(PF_INET, SOCK_STREAM, 0); // Create the socket

    // Configure settings of the server address struct
    serverAddr.sin_family = AF_INET;                               //Address family = Internet
    serverAddr.sin_port = htons(PORT);                             //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");           //Set IP address to localhost
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    // bindCheck = bind(entrySocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)); //Bind the address struct to the socket
    // if (bindCheck < 0)
    // {
    //     perror("[-]Error in bind");
    //     exit(1);
    // }
    // printf("[+]Binding successfull.\n");

    // // Listen on the socket, with 5 max connection requests queued
    // if (listen(entrySocket, 5) == 0)
    // {
    //     printf("[+]Listening....\n");
    // }
    // else
    // {
    //     printf("[-]Error in listening");
    // }


    connectionSocket = accept(entrySocket, (struct sockaddr *)&serverStorage, &addr_size);

    // SENDING AND RECEIVING AFTER THIS POINT
    //=======================================

    struct Query query;
    struct Query *queryPtr = &query;

    // assigns input data to Query struct
    strcpy(queryPtr->employeeName, "Jerry Seinfeld");
    strcpy(queryPtr->jobTitle, "Chocolate Pornstar");
    strcpy(queryPtr->status, "PP");

    send(connectionSocket, queryPtr->employeeName, EMPLOYEENAME_LEN, 0);
    send(connectionSocket, queryPtr->jobTitle, JOBTITLE_LEN, 0);
    send(connectionSocket, queryPtr->status, STATUS_LEN, 0);

    printf("\n[+]Data sent successfully to assistant.\n");
}


void receiveQueryFromAssistant()
{
    int entrySocket, connectionSocket; // socket file descriptors
    int bindCheck;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    // The three arguments are: Internet domain, Stream socket, Default protocol (TCP in this case)
    entrySocket = socket(PF_INET, SOCK_STREAM, 0); // Create the socket

    // Configure settings of the server address struct
    serverAddr.sin_family = AF_INET;                               //Address family = Internet
    serverAddr.sin_port = htons(PORT);                             //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");           //Set IP address to localhost
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

    for (int i = 0; i < 2; i++)
    {
        // Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;
        connectionSocket = accept(entrySocket, (struct sockaddr *)&serverStorage, &addr_size);

        // SENDING AND RECEIVING AFTER THIS POINT
        //=======================================

        char buffer[3][1024];

        recv(connectionSocket, buffer[0], EMPLOYEENAME_LEN, 0); //Read the message from the server into the buffer
        recv(connectionSocket, buffer[1], JOBTITLE_LEN, 0);     //Read the message from the server into the buffer
        recv(connectionSocket, buffer[2], STATUS_LEN, 0);       //Read the message from the server into the buffer

        printf("\n[+]Data received from assistant via socket:\n\n%s\n%s\n%s\n", buffer[0], buffer[1], buffer[2]); //Print the received message
    }
}