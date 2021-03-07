#include "header.h"
int searchFile(char *fname, char *employeeName, char *jobTitle, char *status);

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
    printf("\nRECEIVED:\nEmployee Name: %s\nJob Title: %s\nStatus: %s\n", query.employeeName, query.jobTitle, query.status); // Print the read message

    FILE *f; // file pointer
    f = fopen("History.txt", "a+"); // opens file for appending

    char fname[] = "History.txt"; // name of file to search 

    if (searchFile(fname, query.employeeName, query.jobTitle, query.status) != 0) // a match was found
    {
        // PRINT EMPLOYEE INFORMATION FROM THE HISTORY FILE TO THE TERMINAL
    }
    else // a match wasn't found
    {
        // NEED TO MAKE SOCKET CONNECTION TO SERVER TO SEND QUERY

        // THEN RECEIVE DATA FROM SERVER AND PRINT TO NEW TERMINAL

        // THEN WRITE EMPLOYEE TO NEW EMPLOYEE TO HISTORY FILE
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
    FILE *f; // file pointer
    int line_num = 1; // keeps track of the line number 
    int find_result = 0; // number of matches found
    char temp[512]; // stores the current read line

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
        printf("\nSorry, couldn't find a match.\n");
    }

    if (f)
    {
        fclose(f); //Close the file if still open.
    }
    return find_result;
}