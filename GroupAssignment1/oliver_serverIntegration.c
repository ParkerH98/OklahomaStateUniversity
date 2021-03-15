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

// Function Searches the Salary.txt file by the ID passed in on the employeeStructure object.
void* SalarySearch(void *arg){
	struct employeeStructure *test = (struct employeeStructure *)arg;
	
	FILE *fp;
	char string[100];
	int id;
	float basePay;
	float overtimePay;
    float benefit;

    // Open File.
	fp = fopen("inputTxtFiles//Salary.txt","r");
    // Iterate across the File, checking the ID Value from each line.
	while(fgets(string, 100, fp)){
		sscanf(string,"%d",&id);
        // IF we find the ID we're looking for, read the whole line into the DataStructure directly if possible,
        // and bounce it through a different thing if the compiler screams too loudly.
		if (id == test->id){

			// NOTE: For some reason, the compiler identifies the pointers to the Employee Structure object as
			// being pointers to a double, instead of a float. I've worked around by giving it some local
			// variables to play with. Probably a minor slowdown here, but since we only read full lines once per
			// lookup it shouldn't contribute too much to runtime as the problem scales.

			sscanf(string,"%d\t%[^\t]\t%f\t%f\t%f\t%s",&id,test->jobTitle,&basePay,&overtimePay,&benefit,test->status);
			test->basePay = basePay;
			test->overtimePay = overtimePay;
			test->benefit = benefit;
			break;
		}
	}
	fclose(fp);
	return NULL;
}

// Virtually identical to the Salary Search function above. Searches the Satisfaction file.
void* SatisfactionSearch(void *arg){
	struct employeeStructure *test = (struct employeeStructure *)arg;
	
	FILE *fp;
	char string[100];
	int id;
	float satisfactionLevel;
    int i = 0;

    // Open up the file.
	fp = fopen("inputTxtFiles//Satisfaction.txt","r");

    // Iterate across the file, checking IDs. When we find the right one, scan in the line.
	while(fgets(string, 100, fp)){
		sscanf(string,"%d",&id);
		if (id == test->id){

            // Yes, I'm using a (frankly hideous) scanf to find these. 
            // We're working with a fixed format so the usual problems with scanf are absent.

			sscanf(string,"%d\t%f\t%d\t%d\t%d\t%d\t%d",&id,&satisfactionLevel,&test->numberProject,&test->averageMonthlyHours,
				&test->yearsInCompany,&test->workAccident,&test->promotionsLast5Years);
			test->satisfactionLevel = satisfactionLevel;

			break;
		}
	}
	fclose(fp);
	return NULL;
}

// ThreadSpawn takes in an Employee Structure Pointer, and then spawns the threads to
// search the Salary and Satisfaction files.
void ThreadSpawn(struct employeeStructure *target){

	pthread_t TID_1;
	pthread_t TID_2;

	pthread_create(&TID_1, NULL, SalarySearch, target);
	pthread_create(&TID_2, NULL, SatisfactionSearch, target);
	pthread_join(TID_1, NULL);
	pthread_join(TID_2, NULL);

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

    // This function generates threads.
	ThreadSpawn(pEmployeeStruct);

    printf("%s\n",pEmployeeStruct->status);
    printf("%s\n",pEmployeeStruct->jobTitle);

    if(strcmp(pEmployeeStruct->status, pQueryFromClient->status) == 0 && strcmp(pEmployeeStruct->jobTitle, pQueryFromClient->jobTitle) == 0){
        printf("Acceptable entry.\n");
        // TODO: Need to have things added to a Linked List here.
    }
   
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
    

    // printing testing
    printf("%s\n",pEmployeeStruct->employeeName);
    printf("%d\n",pEmployeeStruct->id);
    printf("%s\n",pEmployeeStruct->status);
    printf("%s\n",pEmployeeStruct->jobTitle);
    free(pEmployeeStruct);
    
	return 0;
}