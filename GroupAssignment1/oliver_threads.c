#include <pthread.h>
#include <stdio.h>
#include <string.h>

struct employeeStructure
{
    int id;
    char employeeName[30];
    char jobTitle[128];
    float basePay;
    float overtimePay;
    float benefit;
    char status[3];
    float satisfactionLevel;
    int numberProject;
    int averageMonthlyHours;
    int yearsInCompany;
    int workAccident;
    int promotionsLast5Years;
    int duplicateExists;
};

void* SalarySearch(void *arg){
	struct employeeStructure *test = (struct employeeStructure *)arg;
	
	FILE *fp;
	char string[100];
	int id;
	float basePay;
	float overtimePay;
    float benefit;

	fp = fopen("inputTxtFiles//Salary.txt","r");

	while(fgets(string, 100, fp)){
		sscanf(string,"%d",&id);
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

void* SatisfactionSearch(void *arg){
	struct employeeStructure *test = (struct employeeStructure *)arg;
	
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

void ThreadSpawn(struct employeeStructure *target){

	pthread_t TID_1;
	pthread_t TID_2;

	pthread_create(&TID_1, NULL, SalarySearch, target);
	pthread_create(&TID_2, NULL, SatisfactionSearch, target);
	pthread_join(TID_1, NULL);
	pthread_join(TID_2, NULL);

};

int SSThreadsTest(){

	printf("Testing Search Threads for Salary and Satisfaction Elements.\n");

	struct employeeStructure a;

	a.id = 17;
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