#include "header.h"
#include <sys/socket.h>



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
};

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