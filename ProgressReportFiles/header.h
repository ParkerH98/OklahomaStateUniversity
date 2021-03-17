#ifndef HEADER_H
#define HEADER_H

#define EMPLOYEENAME_LEN 30
#define JOBTITLE_LEN 128
#define STATUS_LEN 3

struct listEntry{
    struct employeeStructure* data;
    struct listEntry* next;
    struct listEntry* last;
};

struct listMonitor{
    struct listEntry* head;
    struct listEntry* tail;
};

struct query{
    char employeeName[EMPLOYEENAME_LEN];
    char jobTitle[JOBTITLE_LEN];
    char status[STATUS_LEN];
};

struct employeeStructure{
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

#endif