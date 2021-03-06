#include "header.h"
int searchFile(char *fname, char *employeeName, char *jobTitle, char *status);

void assistant()
{
    struct Query query;

    query = pipeReceive(); // assistant receives query from Manager
    printf("\nRECEIVED:\nEmployee Name: %s\nJob Title: %s\nStatus: %s\n", query.employeeName, query.jobTitle, query.status); // Print the read message


    FILE *f;

    f = fopen("History.txt", "a+");

    char fname[] = "History.txt";

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

    // fprintf(f, "Employee Name: %s Job Title: %s Status: %s\n", receivedPtr->employeeName, receivedPtr->jobTitle, receivedPtr->status);
}

/*
---------------------------------------------------------
Searches an input file for a specific employee's name, 
job title, and status.

Params: 
Return: an int representing the number of matches found in the file
*/
int searchFile(char *fname, char *employeeName, char *jobTitle, char *status)
{
    FILE *fp;
    int line_num = 1;
    int find_result = 0;
    char temp[512];

    if ((fp = fopen(fname, "r")) == NULL)
    {
        return (-1);
    }

    while (fgets(temp, 512, fp) != NULL)
    {
        if ((strstr(temp, employeeName)) != NULL && (strstr(temp, jobTitle)) != NULL && (strstr(temp, status)) != NULL)
        {
            printf("A match found on line: %d\n", line_num);
            printf("\n%s\n", temp);
            find_result++;
        }
        line_num++;
    }

    if (find_result == 0)
    {
        printf("\nSorry, couldn't find a match.\n");
    }

    //Close the file if still open.
    if (fp)
    {
        fclose(fp);
    }
    return find_result;
}