
#include <stdlib.h> // needed for file operations
#include <stdio.h> // Baisc standard I/O like printf
#include <string.h> // required for strlen
#include <unistd.h> // defines standard symbolic constants and types
#include <sys/types.h> // basic derived types like pid_t
#include <sys/stat.h> //required for mkfifo (i.e. defines data returned by the stat() function: get file status)
#include <fcntl.h> //required for open (i.e. file control options)

// struct buffer lengths
#define EMPLOYEENAME_LEN 30
#define JOBTITLE_LEN 128
#define STATUS_LEN 3

#define TESTING_LOOP 1

extern int iterationCount = 1;
extern char IP[16];


struct Query
{
    char employeeName[EMPLOYEENAME_LEN];
    char jobTitle[JOBTITLE_LEN];
    char status[STATUS_LEN];
};

struct EmployeeStructure
{
    int id;
    char employeeName[EMPLOYEENAME_LEN];
    char jobTitle[JOBTITLE_LEN];
    float basePay;
    float overtimePay;
    float benefit;
    char status[STATUS_LEN];
    float satisfactionLevel;
    int numberProject;
    int averageMonthlyHours;
    int yearsInCompany;
    int workAccident;
    int promotionsLast5Years;
    int duplicateExists;
};

void manager();
void assistant();