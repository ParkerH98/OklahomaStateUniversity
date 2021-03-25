#include "header.h"
#include "combined_pipes.c"
#include "combined_clientOperations.c"

/*

*/
int writeFile(char *fname, struct EmployeeStructure newLine, int writePos){
    FILE *fp;
    FILE *fp2;
    char tempFName[] = "HistoryTemp.c";
    char temp[512];
    int write = 0;
    int i = 0;
    int writePosition = writePos;
    
    printf("Writing File.");

    if ((fp = fopen(fname, "r")) == NULL){
        return (-1);
    }

    if ((fp2 = fopen(tempFName, "w")) == NULL){
        return(-1);
    }

    while(fgets(temp,512,fp) != NULL){
        printf("%d == %d ", i, writePosition);
        if (i == writePosition && write == 0){
            printf("New Line In");
            fprintf(fp2,"%d\t%s\t%s\t%f\t%f\t%f\t%s\t%f\t%d\t%d\t%d\t%d\t%d\n",
            newLine.id,newLine.employeeName,newLine.jobTitle,newLine.basePay,newLine.overtimePay,
            newLine.benefit,newLine.status,newLine.satisfactionLevel,newLine.numberProject,
            newLine.averageMonthlyHours,newLine.yearsInCompany,newLine.workAccident,newLine.promotionsLast5Years);
            write = 1;
        }
        else{
            fprintf(fp2,"%s", temp);
        }
        i = i+1;
    }
    if (write == 0){
        printf("New Line In");
        fprintf(fp2,"%d\t%s\t%s\t%f\t%f\t%f\t%s\t%f\t%d\t%d\t%d\t%d\t%d",
        newLine.id,newLine.employeeName,newLine.jobTitle,newLine.basePay,newLine.overtimePay,
        newLine.benefit,newLine.status,newLine.satisfactionLevel,newLine.numberProject,
        newLine.averageMonthlyHours,newLine.yearsInCompany,newLine.workAccident,newLine.promotionsLast5Years);
        write = 1;
    }
    fclose(fp2);
    fclose(fp);
    remove("history.txt");
    rename("HistoryTemp.c","history.txt");
    return 0;
};

/*
---------------------------------------------------------
Searches an input file for a specific employee's name, 
job title, and status.

Params: pointers to the file name, and pointers to the employee name, job title, and status of the query in question
Return: an int representing the number of matches found in the file
*/

int searchFile(char *fname, char *employeeName, char *jobTitle, char *status, struct EmployeeStructure *newLine)
{
    FILE *f;             // file pointer
    int line_num = 1;    // keeps track of the line number
    int numMatches = 0; // number of matches found
    char temp[512];      // stores the current read line

    // opens file for reading
    if ((f = fopen(fname, "r")) == NULL) { return (-1); }

    while (fgets(temp, 512, f) != NULL) // goes through file line by line
    {
        if ((strstr(temp, employeeName)) != NULL && (strstr(temp, jobTitle)) != NULL && (strstr(temp, status)) != NULL) // searches for the specific employee attributes
        {
            printf("A match found on line: %d\n", line_num);
            printf("\n%s\n", temp);
            sscanf(temp,"%d\t%s\t%s\t%lf\t%lf\t%lf\t%s\t%f\t%d\t%d\t%d\t%d\t%d\n",
            &newLine->id,newLine->employeeName,newLine->jobTitle,&newLine->basePay,&newLine->overtimePay,
            &newLine->benefit,newLine->status,&newLine->satisfactionLevel,&newLine->numberProject,
            &newLine->averageMonthlyHours,&newLine->yearsInCompany,&newLine->workAccident,&newLine->promotionsLast5Years);
            numMatches++;
        }
        line_num++;
    }

    // no results found
    if (numMatches == 0) { printf("\nQuery does not exist in history file...forwarding request to server.\n"); }

    //Close the file if still open.
    if (f) { fclose(f); }
    return numMatches; 
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
    int writePosition = 0;
    
    query = pipeReceive();                                                                                                   // assistant receives query from Manager
    printf("\nAssistant: RECEIVED FROM MANAGER VIA PIPE:\nEmployee Name: %s\nJob Title: %s\nStatus: %s\n", query.employeeName, query.jobTitle, query.status); // Print the read message

    FILE *f; // file pointer
    f = fopen("history.txt", "a+"); // opens file for appending
    fclose(f);

    char fname[] = "history.txt"; // name of file to search

    if (searchFile(fname, query.employeeName, query.jobTitle, query.status, &employeeStruct) != 0) // a match was found
    {
        // Parker's function to print to a new terminal will go here
        printf("\nAssistant: ----------------FOUND MATCHED INPUT IN HISTORY-----------------\n");
        printf("Employee ID: %d",employeeStruct.id);
    }
    // else // a match wasn't found
    // {
        // printf("HERE---------------------------------");
       
    else{
        // printf("\nAssistant: ----------------NOT FOUND MATCHED INPUT IN HISTORY-----------------\n"); // this line prints in the searchFile function
        sendQueryAndGetEmployeeStruct(query, &employeeStruct);
        writeFile("History.txt",employeeStruct,writePosition);
        writePosition = (writePosition + 1)%10;
    }
        // Parker's function to print to a new terminal will go here
    // }
}



void client(){
    
   
    for (int i = 0; i < TESTING_LOOP; i++)
    {
    // for (int i = 0; i < TESTING_LOOP; i++)
    // {
        printf("==========CLIENT LOOP START==========\n");
        pid_t pid;
    
        pid = fork(); // creates a child process
        
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
            // exit(1);
            
            // exit(1);
            
        }
        else
        {
            printf("fork error");
            exit(1);
        }
        printf("==========CLIENT LOOP END==========\n");
    }
}