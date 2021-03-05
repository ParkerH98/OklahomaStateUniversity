#include "header.h"


void pipeSend(char *employeeName, char *jobTitle, char *status)
{
    int fd; // file descriptor

    struct Query send;
    struct Query *sendPtr = &send;

    strcpy(sendPtr->employeeName, employeeName);
    strcpy(sendPtr->jobTitle, jobTitle);
    strcpy(sendPtr->status, status);

    printf("Employee Name: %s\n Job Title: %s\n Status: %s\n", sendPtr->employeeName, sendPtr->jobTitle, sendPtr->status); // Print the read message

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

int main()
{
    //EmployeeName, JobTitle and Status
    // NATHANIEL FORD GENERAL MANAGER-METROPOLITAN TRANSIT AUTHORITY PT
    // CAPTAIN III (POLICE DEPARTMENT) FT
    // GARY JIMENEZ CAPTAIN III (POLICE DEPARTMENT) FT

    char employeeName[3][30];
    strcpy(employeeName[0], "NATHANIEL FORD");
    strcpy(employeeName[1], "GARY JIMENEZ");
    strcpy(employeeName[2], "ALBERT PARDINI");

    char jobTitle[3][128];
    strcpy(jobTitle[0], "GENERAL MANAGER-METROPOLITAN TRANSIT AUTHORITY");
    strcpy(jobTitle[1], "CAPTAIN III (POLICE DEPARTMENT)");
    strcpy(jobTitle[2], "CAPTAIN III (POLICE DEPARTMENT)");

    char status[3][3];
    strcpy(status[0], "PT");
    strcpy(status[1], "FT");
    strcpy(status[2], "Ft");

    pipeSend(employeeName[1], jobTitle[1], status[1]);
    return 0;
}