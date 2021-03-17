#ifndef HEADER_H
#define HEADER_H

#define EMPLOYEENAME_LEN 30
#define JOBTITLE_LEN 128
#define STATUS_LEN 3

struct ListEntry{
    struct EmployeeStructure* data;
    struct ListEntry* next;
    struct ListEntry* last;
};

struct ListMonitor{
    struct ListEntry* head;
    struct ListEntry* tail;
};

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

#endif