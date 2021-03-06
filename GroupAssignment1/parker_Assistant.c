#include "header.h"
int searchFile(char *fname, char *employeeName, char *jobTitle, char *status);

void assistant()
{
    pipeReceive();
}


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