#include "header.h"
void manager()
{
    struct Query query; // stores query information
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