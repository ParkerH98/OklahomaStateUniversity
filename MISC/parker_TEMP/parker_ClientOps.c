#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h> 
struct EmployeeStructure * clientSocket_SendReceive(char *employeeName, char *jobTitle, char *status);
int searchFile(char *fname, char *employeeName, char *jobTitle, char *status);
void runClient();
void serverSocket_SendReceive();
void sendResultToAssistant();
void receiveResultFromServer();
void printToTerminal(struct EmployeeStructure *employeePtr);

// int main()
// {
//     pid_t pid;
//     pid = fork(); // creates a child process

//     if (pid == 0) // child process
//     {
//         runServer();

//         exit(0);
//     }
//     else if (pid > 0) // parent process
//     {
//         runClient(); // runs manager and assistant functions
//     }

//     return 0;
// }


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
        struct EmployeeStructure employee;
        struct EmployeeStructure *employeePtr = clientSocket_SendReceive(query.employeeName, query.jobTitle, query.status); // sends query to Server

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

void printToTerminal(struct EmployeeStructure *employeePtr)
{
    system("gnome-terminal --  bash -c \"tty; exec bash\""); // opens a new terminal

    int file = open("/dev/pts/2", O_WRONLY); // sets the gnome-terminal as a file to write to
    int stdoutDescriptor = dup(1); // copies the file descriptor for stdout

    dup2(file, 1); // writes the stdout file descriptor to that of the new gnome-terminal

    printf("Id: %d\n", employeePtr->id);
    printf("Employee Name: %s\n", employeePtr->employeeName);
    printf("Job Title: %s\n", employeePtr->jobTitle);
    printf("Base Pay: %f\n", employeePtr->basePay);
    printf("Overtime Pay: %f\n", employeePtr->overtimePay);
    printf("Benefit: %f\n", employeePtr->benefit);
    printf("Status: %s\n", employeePtr->status);
    printf("Satisfaction Level: %f\n", employeePtr->satisfactionLevel);
    printf("Number of Projects: %d\n", employeePtr->numberProject);
    printf("Average Monthly Hours: %d\n", employeePtr->averageMonthlyHours);
    printf("Company Time (Years): %d\n", employeePtr->yearsInCompany);
    printf("Work Accident: %d\n", employeePtr->workAccident);
    printf("Promotion in Last 5 Years: %d\n", employeePtr->promotionsLast5Years);
    printf("Should display in a new window\n"); // tests that stdout prints to new terminal
    printf("===================================================\n\n");

    dup2(stdoutDescriptor, 1); // sets the stdout file descriptor back thereby undoing the change
    printf("Should display in vscode\n"); // tests the stdout prints back in original location
} 