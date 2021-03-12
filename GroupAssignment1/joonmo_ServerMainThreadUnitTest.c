
// Run: Use gcc add_threads.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define MAX 9000000000 // 9 billion times

#define EMPLOYEENAME_LEN 30
#define JOBTITLE_LEN 128
#define STATUS_LEN 3

struct employeeStructure{

    int id;

    char employeeName[30];

    char jobTitle[50];

    float basePay;

    float overtimePay;

    float benefit;

    char status[50];

    float satisfactionLevel;

    int numberProject;

    int averageMonthlyHours;

    int yearsInCompany;

    int workAccident;

    int promotionsLast5Years;

    int duplicateExists;

};

struct Query
{
    char employeeName[EMPLOYEENAME_LEN];
    char jobTitle[JOBTITLE_LEN];
    char status[STATUS_LEN];
};

void *mainTheadFunc(void *queryFromClient)
{
    struct Query* pQueryFromClient = queryFromClient;
	struct employeeStructure* pEmployeeStruct = malloc(sizeof *pEmployeeStruct);
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
            // printf("%s\n", employeeName);
            // printf("%d\n", employeeID);
            break;
        }
    }
    fclose(fp);

    // 	//Micheal Portion ( pEmployeeStruct->id is ready)
	
	
	
    // 	//


   
    return pEmployeeStruct;
}
int main()
{

    pthread_t mainThread;
    struct Query queryFromClient;
    void* pTemp;
    struct employeeStructure* pEmployeeStruct;
    
	// This Testing examples
	strcpy(queryFromClient.employeeName, "NATHANIEL FORD");
	strcpy(queryFromClient.jobTitle, "GENERAL MANAGER-METROPOLITAN TRANSIT AUTHORITY");
	strcpy(queryFromClient.status, "PT");
    if (pthread_create(&mainThread, NULL, mainTheadFunc, (void *)&queryFromClient) != 0) {	// thread1 create
        printf("Thread1 failed\n");
        return -1;
    }
	pthread_join(mainThread, &pTemp);	/* Wait until thread1 is finished */
    pEmployeeStruct = pTemp;
    
    //send 

    // printing testing
    printf("%s\n",pEmployeeStruct->employeeName);
    printf("%d\n",pEmployeeStruct->id);
    free(pEmployeeStruct);
	return 0;
}
