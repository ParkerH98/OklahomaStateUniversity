#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h> // needed for file operations
#include <stdio.h> // Baisc standard I/O like printf
#include <string.h> // required for strlen
#include <unistd.h> // defines standard symbolic constants and types
#include <sys/types.h> // basic derived types like pid_t
#include <sys/stat.h> //required for mkfifo (i.e. defines data returned by the stat() function: get file status)
#include <fcntl.h> //required for open (i.e. file control options)
#include <sys/wait.h> // used for wait function 
#include <netinet/in.h> // needed for socket connections
#include <sys/socket.h> // needed for socket connections
#include <arpa/inet.h> 
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#define EMPLOYEENAME_LEN 30
#define JOBTITLE_LEN 128
#define STATUS_LEN 3
#define HISTORYMAX 10

#define PORT 9007

extern int iterationCount;
extern char IP[16];

struct Query{
    char employeeName[EMPLOYEENAME_LEN];
    char jobTitle[JOBTITLE_LEN];
    char status[STATUS_LEN];
};

struct EmployeeStructure{
    int id;
    char employeeName[EMPLOYEENAME_LEN];
    char jobTitle[JOBTITLE_LEN];
    double basePay;
    double overtimePay;
    double benefit;
    char status[STATUS_LEN];
    float satisfactionLevel;
    int numberProject;
    int averageMonthlyHours;
    int yearsInCompany;
    int workAccident;
    int promotionsLast5Years;
    int duplicateExists;
};
struct EmployeeStack{
    struct EmployeeStructure data;
    struct EmployeeStack *next;
};

#ifndef CON_LC
#define CON_LC


// Courtesy of Joonmo Koo
void convertToLowerCase (char* string) {

   int i = 0;
   char c;
   // char str[] = "JOONMO KOO";
   
   while(string[i]) {
      // putchar (toupper(str[i]));
      string[i] = tolower(string[i]);
      i++;
   }
}

#endif

#endif