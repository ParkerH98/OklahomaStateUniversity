#include "parker_SocketConnections.c"
void sendResultToAssistant();
void testSend();

    int
    main()
{

    receiveQueryFromAssistant();
    sendResultToAssistant();
    sendResultToAssistant();
    sendResultToAssistant();

    // testSend();

    return 0;
}


/*
---------------------------------------------------------
Listens for an incoming socket connection from the Assistant
and then sends the results from the query request back to the 
Assistant via the socket connection.

Params: none
Return: void
*/
void sendResultToAssistant()
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
    serverAddr.sin_family = AF_INET; //Address family = Internet
    serverAddr.sin_port = htons(7892); //Set port number, using htons function to use proper byte order
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

    struct Query query;
    struct Query *queryPtr = &query;

    // assigns input data to Query struct
    strcpy(queryPtr->employeeName, "Jerry Seinfeld");
    strcpy(queryPtr->jobTitle, "Chocolate Pornstar");
    strcpy(queryPtr->status, "PP");

    send(connectionSocket, queryPtr->employeeName, EMPLOYEENAME_LEN, 0);
    send(connectionSocket, queryPtr->jobTitle, JOBTITLE_LEN, 0);
    send(connectionSocket, queryPtr->status, STATUS_LEN, 0);

    printf("[+]Data sent successfully.\n");
}

void testSend(){

}