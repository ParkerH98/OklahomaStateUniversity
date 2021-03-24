#include "header.h"
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 9011

int inet_addr();

char IP[16];

/*
---------------------------------------------------------
Searches an input file for a specific employee's name, 
job title, and status.

Params: pointers to the file name, and pointers to the employee name, job title, and status of the query in question
Return: an int representing the number of matches found in the file
*/
int searchFile(char *fname, char *employeeName, char *jobTitle, char *status)
{
    FILE *f;            // file pointer
    int line_num = 1;   // keeps track of the line number
    int numMatches = 0; // number of matches found
    char temp[512];     // stores the current read line

    // opens file for reading
    if ((f = fopen(fname, "r")) == NULL) { return (-1); }

    while (fgets(temp, 512, f) != NULL) // goes through file line by line
    {
        if ((strstr(temp, employeeName)) != NULL && (strstr(temp, jobTitle)) != NULL && (strstr(temp, status)) != NULL) // searches for the specific employee attributes
        {
            printf("A match found on line: %d\n", line_num);
            printf("\n%s\n", temp);
            numMatches++;
        }
        line_num++;
    }
    // no results found
    if (numMatches == 0)
    {
        printf("\nCLIENT: Query does not exist in history file...need to forward to server.\n");
    }

    //Close the file if still open.
    if (f)
    {
        fclose(f);
    }
    return numMatches;
}

void printToTerminal(struct Employee employee)
{
    if (iterationCount == 1)
    {
        system("gnome-terminal --  bash -c \"tty; exec bash\""); // opens a new terminal
    }

    int file = open("/dev/pts/2", O_WRONLY); // sets the gnome-terminal as a file to write to
    int stdoutDescriptor = dup(1);           // copies the file descriptor for stdout

    dup2(file, 1); // writes the stdout file descriptor to that of the new gnome-terminal

    printf("Id: %d\n", employee.id);
    printf("Employee Name: %s\n", employee.employeeName);
    printf("Job Title: %s\n", employee.jobTitle);
    printf("Base Pay: %f\n", employee.basePay);
    printf("Overtime Pay: %f\n", employee.overtimePay);
    printf("Benefit: %f\n", employee.benefit);
    printf("Status: %s\n", employee.status);
    printf("Satisfaction Level: %f\n", employee.satisfactionLevel);
    printf("Number of Projects: %d\n", employee.numberProject);
    printf("Average Monthly Hours: %d\n", employee.averageMonthlyHours);
    printf("Company Time (Years): %d\n", employee.yearsInCompany);
    printf("Work Accident: %d\n", employee.workAccident);
    printf("Promotion in Last 5 Years: %d\n", employee.promotionsLast5Years);
    printf("Should display in a new window\n"); // tests that stdout prints to new terminal
    printf("===================================================\n\n");

    dup2(stdoutDescriptor, 1);            // sets the stdout file descriptor back thereby undoing the change
    printf("Should display in vscode\n"); // tests the stdout prints back in original location
}

struct Employee clientSocket_SendReceive(char *employeeName, char *jobTitle, char *status)
{

    printf("IP HERE IS %s\n\n\n\n", IP);

    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    // sets values: Internet domain, Stream socket, Default protocol (TCP in this case)
    clientSocket = socket(PF_INET, SOCK_STREAM, 0); // Create the socket
    if (clientSocket < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;                               //Address family = Internet
    serverAddr.sin_port = htons(PORT);                             //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = inet_addr(IP);                    //Set IP address to localhost
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    // Connect the socket to the server using the address struct
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *)&serverAddr, addr_size);
    if (clientSocket == -1)
    {
        perror("[-]Error in socket");
        exit(1);
    }

    struct Query query;
    struct Query *queryPtr = &query;

    // assigns input data to Query struct
    strcpy(queryPtr->employeeName, employeeName);
    strcpy(queryPtr->jobTitle, jobTitle);
    strcpy(queryPtr->status, status);

    send(clientSocket, queryPtr, sizeof(struct Query), 0);
    printf("CLIENT: Query sent to server.\n\n");

    struct Employee employee;
    struct Employee *employeePtr = &employee;

    read(clientSocket, employeePtr, sizeof(struct Employee));

    printf("CLIENT: Result received from server.\n");
    printf("Id: %d\n", employee.id);
    printf("Employee Name: %s\n", employee.employeeName);
    printf("Job Title: %s\n", employee.jobTitle);
    printf("Base Pay: %f\n", employee.basePay);
    printf("Overtime Pay: %f\n", employee.overtimePay);
    printf("Benefit: %f\n", employee.benefit);
    printf("Status: %s\n", employee.status);
    printf("Satisfaction Level: %f\n", employee.satisfactionLevel);
    printf("Number of Projects: %d\n", employee.numberProject);
    printf("Average Monthly Hours: %d\n", employee.averageMonthlyHours);
    printf("Company Time (Years): %d\n", employee.yearsInCompany);
    printf("Work Accident: %d\n", employee.workAccident);
    printf("Promotion in Last 5 Years: %d\n", employee.promotionsLast5Years);

    close(clientSocket);
    return employee;
}

void serverSocket_SendReceive()
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
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);                //Sets IP to accept from any IP address
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    bindCheck = bind(entrySocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)); //Bind the address struct to the socket
    if (bindCheck < 0)
    {
        perror("[-]Error in bind");
        exit(1);
    }
    // printf("[+]Binding successfull.\n");

    // Listen on the socket, with 5 max connection requests queued
    if (listen(entrySocket, 5) == 0)
    {
        printf("SERVER: Listening....\n");
    }
    else
    {
        printf("[-]Error in listening");
    }

    for (int i = 0; i < TESTING_LOOP; i++)
    {
        // Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;
        connectionSocket = accept(entrySocket, (struct sockaddr *)&serverStorage, &addr_size);

        struct Query query;
        struct Query *queryPtr = &query;

        recv(connectionSocket, queryPtr, sizeof(struct Query), 0);                                                                      //Read the message from the server into the buffer
        printf("SERVER: Query received from assistant:\n\n%s\n%s\n%s\n", queryPtr->employeeName, queryPtr->jobTitle, queryPtr->status); //Print the received message

        struct Employee employee;
        struct Employee *employeePtr = &employee;

        employeePtr->id = 15000;
        strcpy(employeePtr->employeeName, "BRIAN BENSON");
        strcpy(employeePtr->jobTitle, "IS BUSINESS ANALYST");
        employeePtr->basePay = 78059.8;
        employeePtr->overtimePay = 0;
        employeePtr->benefit = 0;
        strcpy(employeePtr->status, "FT");
        employeePtr->satisfactionLevel = 0.37;
        employeePtr->numberProject = 2;
        employeePtr->averageMonthlyHours = 158;
        employeePtr->yearsInCompany = 3;
        employeePtr->workAccident = 0;
        employeePtr->promotionsLast5Years = 0;

        send(connectionSocket, employeePtr, sizeof(struct Employee), 0);
        printf("\nSERVER: Result sent to assistant.\n\n");
    }
}
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

    close(fd); // Close the pipe
    return received;
}

void runClient()
{
    for (int i = 0; i < TESTING_LOOP; i++)
    {
        pid_t pid;
        pid = fork(); // creates a child process

        if (pid == 0) // child process
        {
            manager(); // asking user for input query

            exit(0);
        }
        else if (pid > 0) // parent process
        {
            assistant(); // fetching query results for the Manager process
        }
        else
        {
            printf("fork error");
            exit(1);
        }
    }
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

    // printf("Enter an employee name.\n"); // gets and stores employee name into Query struct
    // fgets(queryPtr->employeeName, EMPLOYEENAME_LEN, stdin);
    // strtok(queryPtr->employeeName, "\n");

    // printf("Enter a job title.\n"); // gets and stores job title into Query struct
    // fgets(queryPtr->jobTitle, JOBTITLE_LEN, stdin);
    // strtok(queryPtr->jobTitle, "\n");

    // printf("Enter a status.\n"); // gets and stores status into Query struct
    // fgets(queryPtr->status, STATUS_LEN, stdin);
    // strtok(queryPtr->status, "\n");

    strcpy(queryPtr->employeeName, "BRIAN BENSON");
    strcpy(queryPtr->jobTitle, "IS BUSINESS ANALYST");
    strcpy(queryPtr->status, "FT");

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
    struct Query query;                                                                                                                                    // holds user query
    query = pipeReceive();                                                                                                                                 // assistant receives query from Manager
    printf("\nCLIENT: RECEIVED FROM MANAGER VIA PIPE:\nEmployee Name: %s\nJob Title: %s\nStatus: %s\n", query.employeeName, query.jobTitle, query.status); // Print the read message

    FILE *f;                        // file pointer
    f = fopen("History.txt", "a+"); // opens file for appending

    char fname[] = "History.txt"; // name of file to search

    if (searchFile(fname, query.employeeName, query.jobTitle, query.status) != 0) // a match was found
    {
        // function to print to a new terminal will go here
    }
    else // a match wasn't found
    {
        struct Employee employee = clientSocket_SendReceive(query.employeeName, query.jobTitle, query.status); // sends query to Server
        printToTerminal(employee);                                                                             // prints the received result to a new terminal
        printf("\n====================\nQUERY END\n====================\n\n");

        // function to write to the history file will go here.
    }
    iterationCount++;
}

void runServer()
{
    for (int i = 0; i < TESTING_LOOP; i++)
    {
        serverSocket_SendReceive(); // starts server and begins listening
    }
}