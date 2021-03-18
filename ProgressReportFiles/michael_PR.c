#include "header.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void* SalarySearch(void *arg){
	struct EmployeeStructure *test = (struct EmployeeStructure *)arg;
	
	FILE *fp;
	char string[100];
	int id;
	double basePay;
	double overtimePay;
    double benefit;

	fp = fopen("inputTxtFiles//Salary.txt","r");

	while(fgets(string, 100, fp)){
		sscanf(string,"%d",&id);
		if (id == test->id){

			// NOTE: For some reason, the compiler identifies the pointers to the Employee Structure object as
			// being pointers to a double, instead of a float. I've worked around by giving it some local
			// variables to play with. Probably a minor slowdown here, but since we only read full lines once per
			// lookup it shouldn't contribute too much to runtime as the problem scales.

			sscanf(string,"%d\t%[^\t]\t%lf\t%lf\t%lf\t%s",&id,test->jobTitle,&basePay,&overtimePay,&benefit,test->status);
			test->basePay = basePay;
            printf("%f",basePay);
			test->overtimePay = overtimePay;
			test->benefit = benefit;
			break;
		}
	}
	fclose(fp);
	return NULL;
}

void* SatisfactionSearch(void *arg){
	struct EmployeeStructure *test = (struct EmployeeStructure *)arg;
	
	FILE *fp;
	char string[100];
	int id;
	float satisfactionLevel;
    int i = 0;

	fp = fopen("inputTxtFiles//Satisfaction.txt","r");

	while(fgets(string, 100, fp)){
		sscanf(string,"%d",&id);
		if (id == test->id){

			sscanf(string,"%d\t%f\t%d\t%d\t%d\t%d\t%d",&id,&satisfactionLevel,&test->numberProject,&test->averageMonthlyHours,
				&test->yearsInCompany,&test->workAccident,&test->promotionsLast5Years);
			test->satisfactionLevel = satisfactionLevel;

			break;
		}
	}
	fclose(fp);
	return NULL;
}

void ThreadSpawn(struct EmployeeStructure *target){

	pthread_t TID_1;
	pthread_t TID_2;
    printf("Thread Creation starting.\n");
	pthread_create(&TID_1, NULL, SalarySearch, target);
    printf("Thread One is Live.\n");
	pthread_create(&TID_2, NULL, SatisfactionSearch, target);
    printf("Thread Two is Live.\n");
	pthread_join(TID_1, NULL);
    printf("Thread 1 is Back.");
	pthread_join(TID_2, NULL);
    printf("Thread 2 is Back.");

};

int SSThreadsTest(){

	printf("Testing Search Threads for Salary and Satisfaction Elements.\n");

	struct EmployeeStructure a;

	a.id = 7;
	strcpy(a.employeeName,"Test Name");

	printf("Thread Spawner Starting.\n");
	ThreadSpawn(&a);
	printf("Thread Spawner Finished.\n");

	printf("Checking Output. See individual with Index 17 in associated files to check result.\n");
	printf("Employee Name is Koo's Job. No checks here.\n");
	printf("ID: %d\n",a.id);
	printf("Job Title: %s\n",a.jobTitle);
	printf("Base Pay: %f\n",a.basePay);
	printf("Overtime Pay: %f\n",a.overtimePay);
	printf("Benefit: %f\n",a.benefit);
	printf("Status: %s\n",a.status);
	printf("Satisfaction Level: %f\n",a.satisfactionLevel);
	printf("Number Project: %d\n",a.numberProject);
	printf("Avg. Monthly Hours: %d\n",a.averageMonthlyHours);
	printf("Years in Company: %d\n",a.yearsInCompany);
	printf("Work Accidents: %d\n",a.workAccident);
	printf("Promotions Last 5 Years: %d\n",a.promotionsLast5Years);
}

void enqueue(struct ListMonitor* index, struct EmployeeStructure* payload){
    int first = 0;
    struct ListEntry* temp;

    if (index->head == NULL){
        first = 1;
    }
    temp = malloc(sizeof(struct ListEntry));

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

void disqueue(struct ListMonitor* index, struct ListEntry* target){
    // NOTE: Need to get Pointers to Nowhere working.
    struct ListEntry* temp;
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
    struct ListMonitor* test;
    struct ListEntry* readHead;
    struct EmployeeStructure* person;
    int i = 0;

    printf("Testing Linked Lists");

    test = malloc(sizeof(struct ListMonitor));
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

    printf("\nTest Three: See if ID 4 is missing.\n");
    readHead = test->head;
    while (readHead->next != NULL){
        printf("%d\n",readHead->data->id);
        readHead = readHead->next;
    }
    printf("%d\n",readHead->data->id);

}

void *mainTheadFunc(void *queryFromClient)
{
    struct Query* pQueryFromClient = queryFromClient;
	struct EmployeeStructure* pEmployeeStruct = malloc(sizeof *pEmployeeStruct); //Introduced by M Oliver.
    struct ListMonitor* index = malloc(sizeof (struct ListMonitor)); //Introduced by M Oliver.
	FILE *fp;
    char buff[255];

    // printf("Comes Here\n");
    fp = fopen("inputTxtFiles/Name.txt", "r");
    while (fgets(buff, sizeof(buff), fp)) {
        char * employeeIDString = strtok(buff, "\t");
        // printf("%s\n", employeeIDString);
		int employeeID = atoi(employeeIDString);
        char * employeeName = strtok(NULL, "");
        // printf("%s\n", employeeName);
        if (employeeName[strlen(employeeName)-1] == '\n'){
            employeeName[strlen(employeeName)-1] = 0;
        }
		if(strcmp(employeeName, pQueryFromClient->employeeName) == 0){

            strcpy(pEmployeeStruct->employeeName, employeeName);
            pEmployeeStruct->id = employeeID;

            // ==================================================================================
            // OLIVER'S CODE
            // ==================================================================================
            ThreadSpawn(pEmployeeStruct);
            if (strcmp(pEmployeeStruct->status, pQueryFromClient->status) == 0 && 
                strcmp(pEmployeeStruct->jobTitle, pQueryFromClient->jobTitle) == 0){
                enqueue(index, pEmployeeStruct);
            }
            else{
                free(pEmployeeStruct);
            }


            pEmployeeStruct = malloc(sizeof *pEmployeeStruct);

            // ==================================================================================
            // OLIVER'S CODE
            // ==================================================================================

            // printf("%s\n", employeeName);
            // printf("%d\n", employeeID);
        }
    }
    fclose(fp);
    return index;

}