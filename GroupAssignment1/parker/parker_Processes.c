#include "header.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h> 
void forwardQueryToServer(char *employeeName, char *jobTitle, char *status);
int searchFile(char *fname, char *employeeName, char *jobTitle, char *status);
void runClient();
void receiveQueryFromAssistant();
void sendResultToAssistant();
void runServer();
void receiveResultFromServer();

int main()
{
    pid_t pid;
    pid = fork(); // creates a child process

    if (pid == 0) // child process
    {
        runServer();

        exit(0);
    }
    else if (pid > 0) // parent process
    {
        runClient(); // runs manager and assistant functions
    }

    return 0;
}

void runServer()
{
    for (int i = 0; i < TESTING_LOOP; i++){
        receiveQueryFromAssistant(); // starts server and begins listening
    }
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
    struct Query query; // stores query information
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
    struct Query query; // holds user query
    query = pipeReceive(); // assistant receives query from Manager
    printf("\nCLIENT: RECEIVED FROM MANAGER VIA PIPE:\nEmployee Name: %s\nJob Title: %s\nStatus: %s\n", query.employeeName, query.jobTitle, query.status); // Print the read message

    FILE *f; // file pointer
    f = fopen("History.txt", "a+"); // opens file for appending

    char fname[] = "History.txt"; // name of file to search

    if (searchFile(fname, query.employeeName, query.jobTitle, query.status) != 0) // a match was found
    {
        // Parker's function to print to a new terminal will go here
    }
    else // a match wasn't found
    {
        struct Employee employee;
        struct *employeePtr = forwardQueryToServer(query.employeeName, query.jobTitle, query.status); // sends query to Server

        printToTerminal(employeePtr);

        printf("\n====================\nQUERY END\n====================\n\n");


        // Landon's function to write to the history file will go here.

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
    int numMatches = 0; // number of matches found
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
            numMatches++;
        }
        line_num++;
    }

    if (numMatches == 0) // no results found
    {
        printf("\nCLIENT: Query does not exist in history file...need to forward to server.\n");
    }

    if (f)
    {
        fclose(f); //Close the file if still open.
    }
    return numMatches; 
}