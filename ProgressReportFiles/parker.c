#include "header.h"
#include "header.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include "header.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include "parker_SocketConnections.c"

#define PORT 9001

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

    struct Query send;             // struct to hold query
    struct Query *sendPtr = &send; // pointer to query

    strcpy(sendPtr->employeeName, employeeName); // copies input parameters to the struct to be sent
    strcpy(sendPtr->jobTitle, jobTitle);
    strcpy(sendPtr->status, status);

    // debug print -- remove later
    // printf("\nSENT TO ASSISTANT VIA PIPE:\nEmployee Name: %s\nJob Title: %s\nStatus: %s\n\n", sendPtr->employeeName, sendPtr->jobTitle, sendPtr->status); // Print the read message

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

    struct Query received;                 // holds received user query information
    struct Query *receivedPtr = &received; // pointer to the received query

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

    // debug print -- remove later
    // printf("\nRECEIVED:\nEmployee Name: %s\n Job Title: %s\n Status: %s\n", receivedPtr->employeeName, receivedPtr->jobTitle, receivedPtr->status); // Print the read message

    close(fd); // Close the pipe
    return received;
}


// void forwardQueryToServer(char *employeeName, char *jobTitle, char *status);
int searchFile(char *fname, char *employeeName, char *jobTitle, char *status);
// void receiveResultFromServer();
// int inet_addr();

int main()
{
    // this code will eventually get moved into an overall client function

    // for (int i = 0; i < 2; i++)
    // {
        pid_t pid;
        pid = fork(); // creates a child process

        if (pid == 0) // child process
        {
            manager(); // asking user for input query

            exit(0);
        }
        else if (pid > 0) // parent process
        {
            wait(NULL);
            assistant(); // fetching query results for the Manager process
        }
        else
        {
            printf("fork error");
            exit(1);
        }
    // }

    return 0;
}

/*
---------------------------------------------------------
The main Manager function is in charge of getting user input 
queries.

Params: none
Return: void
*/
void manager()
{
    struct Query query;              // stores query information
    struct Query *queryPtr = &query; // pointer to query information

    printf("Enter an employee name.\n"); // gets and stores employee name into Query struct
    fgets(queryPtr->employeeName, EMPLOYEENAME_LEN, stdin);
    strtok(queryPtr->employeeName, "\n");

    printf("Enter a job title.\n"); // gets and stores job title into Query struct
    fgets(queryPtr->jobTitle, JOBTITLE_LEN, stdin);
    strtok(queryPtr->jobTitle, "\n");

    printf("Enter a status.\n"); // gets and stores status into Query struct
    fgets(queryPtr->status, STATUS_LEN, stdin);
    strtok(queryPtr->status, "\n");

    pipeSend(queryPtr->employeeName, queryPtr->jobTitle, queryPtr->status); // sends the query to the assistant
}

/*
---------------------------------------------------------
The main Assistant function is in charge of getting user input 
queries from the manager. The Assistant then searches a local
cache file and prints the record. If the record isn't found,
then the Assistant then forwards the request to the Server and waits
for the response back from the Server with the retrieved query
information.

Params: none
Return: void
*/
void assistant()
{
    struct Query query;                                                                                                                            // holds user query
    query = pipeReceive();                                                                                                                         // assistant receives query from Manager
    printf("\nRECEIVED FROM MANAGER VIA PIPE:\nEmployee Name: %s\nJob Title: %s\nStatus: %s\n", query.employeeName, query.jobTitle, query.status); // Print the read message

    FILE *f;                        // file pointer
    f = fopen("History.txt", "a+"); // opens file for appending

    char fname[] = "History.txt"; // name of file to search

    if (searchFile(fname, query.employeeName, query.jobTitle, query.status) != 0) // a match was found
    {
        // Parker's function to print to a new terminal will go here
    }
    else // a match wasn't found
    {
        // printf("HERE---------------------------------");
        forwardQueryToServer(query.employeeName, query.jobTitle, query.status); // sends query to Server

        sleep(1);

        receiveResultFromServer();

        printf("\n====================\nQUERY END\n====================\n\n");

        // Landon's function to write to the history file will go here.

        // Parker's function to print to a new terminal will go here
    }
}

/*
---------------------------------------------------------
Searches an input file for a specific employee's name, 
job title, and status.

Params: pointers to the file name, and pointers to the employee name, job title, and status of the query in question
Return: an int representing the number of matches found in the file
*/
int searchFile(char *fname, char *employeeName, char *jobTitle, char *status)
{
    FILE *f;             // file pointer
    int line_num = 1;    // keeps track of the line number
    int find_result = 0; // number of matches found
    char temp[512];      // stores the current read line

    if ((f = fopen(fname, "r")) == NULL) // opens file for reading
    {
        return (-1);
    }

    while (fgets(temp, 512, f) != NULL) // goes through file line by line
    {
        if ((strstr(temp, employeeName)) != NULL && (strstr(temp, jobTitle)) != NULL && (strstr(temp, status)) != NULL) // searches for the specific employee attributes
        {
            printf("A match found on line: %d\n", line_num);
            printf("\n%s\n", temp);
            find_result++;
        }
        line_num++;
    }

    if (find_result == 0) // no results found
    {
        printf("\nQuery does not exist in history file...forwarding request to server.\n");
    }

    if (f)
    {
        fclose(f); //Close the file if still open.
    }
    return find_result;
}

// void sendResultToAssistant();

int main()
{
    receiveQueryFromAssistant();
    // sendResultToAssistant();

    return 0;
}



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
    serverAddr.sin_family = AF_INET;                               //Address family = Internet
    serverAddr.sin_port = htons(PORT);                             //Set port number, using htons function to use proper byte order
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
    recv(clientSocket, buffer[1], JOBTITLE_LEN, 0);     //Read the message from the server into the buffer
    recv(clientSocket, buffer[2], STATUS_LEN, 0);       //Read the message from the server into the buffer

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


void printToTerminal()
{
    system("gnome-terminal --  bash -c \"tty; exec bash\""); // opens a new terminal

    int file = open("/dev/pts/2", O_WRONLY); // sets the gnome-terminal as a file to write to
    int stdoutDescriptor = dup(1);           // copies the file descriptor for stdout

    dup2(file, 1);                              // writes the stdout file descriptor to that of the new gnome-terminal
    printf("Should display in a new window\n"); // tests that stdout prints to new terminal

    dup2(stdoutDescriptor, 1);            // sets the stdout file descriptor back thereby undoing the change
    printf("Should display in vscode\n"); // tests the stdout prints back in original location
}