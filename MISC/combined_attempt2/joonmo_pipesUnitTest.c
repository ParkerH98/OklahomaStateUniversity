#include "header.h"
#include "combined_pipes.c"
#include "combined_clientOperations.c"


// run: gcc joonmo_pipesUnitTest.c -o piptest

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

    // Automate Input
    strcpy(queryPtr->employeeName, "THOMAS SMITH");
	strcpy(queryPtr->jobTitle, "SPECIAL NURSE");
	strcpy(queryPtr->status, "FT");

    pipeSend(queryPtr->employeeName, queryPtr->jobTitle, queryPtr->status); // sends the query to the assistant
    printf("\nManager: Send Query to Assistant VIA PIPE\n");
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
    struct Query query;                                                                                                      // holds user query
    struct EmployeeStructure employeeStruct;
    
    query = pipeReceive();                                                                                                   // assistant receives query from Manager
    printf("\nAssistant: RECEIVED FROM MANAGER VIA PIPE:\nEmployee Name: %s\nJob Title: %s\nStatus: %s\n", query.employeeName, query.jobTitle, query.status); // Print the read message
        // Landon's function to write to the history file will go here.

        // Parker's function to print to a new terminal will go here
    // }
}


int main(){
    
    // pid_t pid;
    
    // pid = fork(); // creates a child process
    for (int i = 0; i < 3; i++)
    {
    // for (int i = 0; i < TESTING_LOOP; i++)
    // {
        pid_t pid;
    
        pid = fork(); // creates a child process
        // printf("==========CLIENT LOOP START==========\n");
        if (pid == 0) // child process
        {
            manager(); // asking user for input query
            printf("The Manager process is done!\n");
            exit(0);
        }
        else if (pid > 0) // parent process
        {
            
            // sleep(2);
            assistant(); // fetching query results for the Manager process
            printf("The Assistant process is done!\n");
            wait(NULL);
            
        }
        else
        {
            printf("fork error");
            exit(1);
        }
        printf("==========CLIENT LOOP END==========\n");
    }
    return 0;
}