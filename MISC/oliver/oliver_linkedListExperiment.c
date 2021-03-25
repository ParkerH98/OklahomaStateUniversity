#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define EMPLOYEENAME_LEN 30
#define JOBTITLE_LEN 128
#define STATUS_LEN 3

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

struct listEntry{
    struct EmployeeStructure* data;
    struct listEntry* next;
    struct listEntry* last;
};

struct listMonitor{
    struct listEntry* head;
    struct listEntry* tail;
};

void enqueue(struct listMonitor* index, struct EmployeeStructure* payload){
    int first = 0;
    struct listEntry* temp;

    if (index->head == NULL){
        first = 1;
    }
    temp = malloc(sizeof(struct listEntry));

    temp->data = payload;
    temp->next = NULL;
    temp->last = index->tail;
    if (!first){
        index->tail->next = temp;
    }
    index->tail = temp;

    if (first){
        index->head = temp;
    }
};

void disqueue(struct listMonitor* index, struct listEntry* target){
    struct listEntry* temp;
    if (target == index->head){
        temp = target;
        index->head = index->head->next;
        index->head->last = NULL;
        free(temp->data);
        free(temp);
    }
    else if (target == index->tail){
        temp = target;
        index->tail = index->tail->last;
        index->tail->next = NULL;
        free(temp->data);
        free(temp);

    }
    else {
        temp = target;
        temp->next->last=temp->last;
        temp->last->next=temp->next;
        free(temp->data);
        free(temp);
    }
};

int LLTest(){
    struct listMonitor* test;
    struct listEntry* readHead;
    struct EmployeeStructure* person;
    int i = 0;

    printf("Testing Linked Lists");

    test = malloc(sizeof(struct listMonitor));
    person = malloc(sizeof(struct EmployeeStructure));

    for (i = 0; i < 10; i++){
        person->id = i;
        enqueue(test, person);
        person = malloc(sizeof(struct EmployeeStructure));
    }

    printf("\nTest One: See if ID from 0-9 are present.\n");

    readHead = test->head;
    while (readHead->next != NULL){
        printf("%d\n",readHead->data->id);
        readHead = readHead->next;
    }
    printf("%d\n",readHead->data->id);

    disqueue(test,test->head);
    disqueue(test,test->tail);

    printf("\nTest Two: See if IDs 0 and 9 have successfully been removed.\n");
    readHead = test->head;
    while (readHead->next != NULL){
        printf("%d\n",readHead->data->id);
        readHead = readHead->next;
    }
    printf("%d\n",readHead->data->id);

    readHead = test->head;
    for (i = 0; i<4; i++){
        if (i==3){
            disqueue(test,readHead);
        }
        readHead = readHead->next;
    }

    printf("\nTest Three: See if ID 4 is missing.");
    readHead = test->head;
    while (readHead->next != NULL){
        printf("%d\n",readHead->data->id);
        readHead = readHead->next;
    }
    printf("%d\n",readHead->data->id);

}