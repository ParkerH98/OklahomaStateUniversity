
// Run: Use gcc add_threads.c -lpthread
#include "header.h"
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>


// Salary Search is the function that takes a EmployeeStructure with a non-empty ID field as input, and finds the information
// for that Employee ID in the SaLary File. It then adds that information to the relevant fields in the Structure.
void* SalarySearch(void *arg){
    // Clone the input pointer so that it's of the right type.
	struct EmployeeStructure *test = (struct EmployeeStructure *)arg;
	
    // Setup relevant variables.
	FILE *fp;
	char string[100];
	int id;
	double basePay;
	double overtimePay;
    double benefit;

    // Open the file.
	fp = fopen("inputTxtFiles//Salary.txt","r");

    // Iterate across the file, looking for the ID we need.
	while(fgets(string, 100, fp)){
		sscanf(string,"%d",&id);
		if (id == test->id){

			// When we find the ID, copy the information over. Yes, this is done using a horrific sscanf. It works for the fixed
            // format we're dealing with, so I'm happy with it.

			sscanf(string,"%d\t%[^\t]\t%lf\t%lf\t%lf\t%s",&id,test->jobTitle,&basePay,&overtimePay,&benefit,test->status);
			test->basePay = basePay;
			test->overtimePay = overtimePay;
			test->benefit = benefit;
			break;
		}
	}
    // Close out the function and return nothing. All changes are saved to the object that was passed in.
	fclose(fp);
	return NULL;
}

//Satisfaction Search is largely identical to Salary Search, with the only difference being the fields that are scanned.
void* SatisfactionSearch(void *arg){
    // Capture the pointer in the proper format.
	struct EmployeeStructure *test = (struct EmployeeStructure *)arg;
	
    // Rig up the input variables.
	FILE *fp;
	char string[100];
	int id;
	float satisfactionLevel;
    int i = 0;

    // Open Text File
	fp = fopen("inputTxtFiles//Satisfaction.txt","r");

    //Iterate across the file, checking for the ID we're looking for.
	while(fgets(string, 100, fp)){
		sscanf(string,"%d",&id);
		if (id == test->id){
            // Grab the important bits.
			sscanf(string,"%d\t%f\t%d\t%d\t%d\t%d\t%d",&id,&satisfactionLevel,&test->numberProject,&test->averageMonthlyHours,
				&test->yearsInCompany,&test->workAccident,&test->promotionsLast5Years);
			test->satisfactionLevel = satisfactionLevel;

			break;
		}
	}
    // Close the file and return nothing.
	fclose(fp);
	return NULL;
}

// This functions spawns the threads we need.
void ThreadSpawn(struct EmployeeStructure *target){
    // Setup Thread ID Holders.
	pthread_t TID_1;
	pthread_t TID_2;
    // Spin up the threads, passing forward the target EmployeeStructure.
	pthread_create(&TID_1, NULL, SalarySearch, target);
	pthread_create(&TID_2, NULL, SatisfactionSearch, target);
    // Wait for the threads to finish.
	pthread_join(TID_1, NULL);
	pthread_join(TID_2, NULL);
};

// Simple test program. Hard-Sets the Employee Name and ID Information we need, then runs.
int SSThreadsTest(){

	printf("Testing Search Threads for Salary and Satisfaction Elements.\n");

    // Setup a fixed EmployeeStructure to search for information on.
	struct EmployeeStructure a;
	a.id = 7;
	strcpy(a.employeeName,"Test Name");

    // Call up THreadSpawn to spawn threads to get the information we care about.
	ThreadSpawn(&a);

    // Print what was found to see if this is working properly.
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


// FUnction to enqueue the information.
void enqueue(struct ListMonitor* index, struct EmployeeStructure* payload){
    int first = 0;              //I'm using this integer as a boolean.
    struct ListEntry* temp;     // This pointer exists to keep track of what we're working with.

    // If the front pointer on the index is Null, we're adding the first item to the linked list.
    if (index->head == NULL){
        first = 1;
    }
    // Create the List Entry that will be added.
    temp = malloc(sizeof(struct ListEntry));
    // Attach the payload, a EmployeeStructure passed in from outside.
    temp->data = payload;
    // Set the next pointer to nothing.
    temp->next = NULL;
    //Hook up the last pointer to the object attached to the tail of the management structure.
    temp->last = index->tail;
    //If this isn't the first, the old tail's next pointer is moved off NULL and onto the new thing.
    if (!first){
        index->tail->next = temp;
    }
    // We then move the tail pointer onto the new thing.
    index->tail = temp;

    // IF this is the first item, we attach the head.
    if (first){
        index->head = temp;
    }
};

//Function to bump from the queue.
void disqueue(struct ListMonitor* index, struct ListEntry* target){
    // NOTE: Need to get Pointers to Nowhere working.
    struct ListEntry* temp;
    // If this is the only item, we need to clear it.
    if (target == index->head && target == index->tail){
        temp = target;
        index->head == NULL;
        index->tail == NULL;
        free(temp->data);
        free(temp);
    }
    // If it's the first item, then we have to move the head pointer forward by one.
    else if (target == index->head){
        // Attach the target to the temp pointer.
        temp = target;
        // Move the head forward one in the queue.
        index->head = index->head->next;
        // Remove the last pointer from the element about to be deleted, and point it to nothing.
        index->head->last = NULL;
        // Free the data and the entry.
        free(temp->data);
        free(temp);
    }
    // If it's the last item, then we have to move the tail pointer back by one.
    else if (target == index->tail){
        temp = target;
        // Move the tail pointer back by one.
        index->tail = index->tail->last;
        // Wipe out the next pointer.
        index->tail->next = NULL;
        // Clear out the data to be removed.
        free(temp->data);
        free(temp);

    }
    // Otherwise, we have to connect the neighbors.
    else {
        temp = target;
        // Redirect all references to the target being removed to the appropriate neighbor.
        temp->next->last=temp->last;
        temp->last->next=temp->next;
        // Then remove the target.
        free(temp->data);
        free(temp);
    }
};



void *mainTheadFunc(void *queryFromClient)
{
    struct Query* pQueryFromClient = queryFromClient;
	struct EmployeeStructure* pEmployeeStruct = malloc(sizeof *pEmployeeStruct);
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
    struct EmployeeStructure* pEmployeeStruct;

	// This Testing examples
	// strcpy(queryFromClient.employeeName, "NATHANIEL FORD");
	// strcpy(queryFromClient.jobTitle, "GENERAL MANAGER-METROPOLITAN TRANSIT AUTHORITY");
	// strcpy(queryFromClient.status, "PT");
    strcpy(queryFromClient.employeeName, "THOMAS SMITH");
	strcpy(queryFromClient.jobTitle, "SPECIAL NURSE");
	strcpy(queryFromClient.status, "FT");
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
