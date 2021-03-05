#include "header.h"

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

void pipeReceive()
{
    int fd; // file descriptor

    struct Query received;
    struct Query *receivedPtr = &received;

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

    // Display the results
    printf("Employee Name: %s\n Job Title: %s\n Status: %s\n", receivedPtr->employeeName, receivedPtr->jobTitle, receivedPtr->status); // Print the read message


    FILE *f;
    f = fopen("History.txt", "a+");

    char fname[] = "History.txt";

    if (searchFile(fname, receivedPtr->employeeName, receivedPtr->jobTitle, receivedPtr->status) == 0){
        // employee not found so send Query to Server

        char myPipe[] = "./NamedPipe"; // FIFO file path
        mkfifo(myPipe, 0666);          // Creating the named file(FIFO)

        if ((fd = open(myPipe, O_WRONLY | O_CREAT)) < 0) // Open FIFO for write only
        {
            printf("1: Error opening..");
        }

        if (write(fd, receivedPtr, sizeof(struct Query)) < 0) // Write on the FIFO
        {
            printf("1: Error writing..");
        }

        close(fd); // Close the pipe
    }


    fprintf(f, "Employee Name: %s Job Title: %s Status: %s\n", receivedPtr->employeeName, receivedPtr->jobTitle, receivedPtr->status);

    close(fd); // Close the pipe
    fclose(f);
}

int main()
{
    pipeReceive();
    return 0;
}