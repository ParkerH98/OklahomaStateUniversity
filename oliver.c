// Michael Oliver
// Group B
// 
#include "header.h"

int searchFile(char *fname, char *employeeName, char *jobTitle, char *status, struct EmployeeStructure *newLine)
{
    FILE *f;             // file pointer
    int line_num = 1;    // keeps track of the line number
    int numMatches = 0; // number of matches found
    char temp[512];      // stores the current read line
	char *token;
	int i = 0;
    if ((f = fopen(fname, "r")) == NULL) // opens file for reading
    {
        return (-1);
    }

	char employeeNameL[strlen(employeeName)];
	strcpy(employeeNameL,employeeName);
	convertToLowerCase(employeeNameL);
	char jobTitleL[strlen(jobTitle)];
	strcpy(jobTitleL,jobTitle);
	convertToLowerCase(jobTitleL);
	char statusL[strlen(status)];
	strcpy(statusL,status);
	convertToLowerCase(statusL);

    while (fgets(temp, 512, f) != NULL) // goes through file line by line
    {
        if ((strstr(temp, employeeNameL)) != NULL && (strstr(temp, jobTitleL)) != NULL && (strstr(temp, statusL)) != NULL) // searches for the specific employee attributes
        {
            printf("A match found on line: %d\n", line_num);

			// Convert the right string to a series of tokens, then feed things into the right field.

			token = strtok(temp,"\t");

			while (token != NULL){
				if (i == 0){
					sscanf(token,"%d",&newLine->id);
				}
				else if (i == 1){
					strcpy(newLine->employeeName, token);
				}
				else if (i == 2){
					strcpy(newLine->jobTitle,token);
				}
				else if (i == 3){
					sscanf(token,"%lf",&newLine->basePay);
				}
				else if (i == 4){
					sscanf(token,"%lf",&newLine->overtimePay);
				}
				else if (i == 5){
					sscanf(token,"%lf",&newLine->benefit);
				}
				else if (i == 6){
					strcpy(newLine->status,token);
				}
				else if (i == 7){
					sscanf(token,"%f",&newLine->satisfactionLevel);
				}
				else if (i == 8){
					sscanf(token,"%d",&newLine->numberProject);
				}
				else if (i == 9){
					sscanf(token,"%d",&newLine->averageMonthlyHours);
				}
				else if (i == 10){
					sscanf(token,"%d",&newLine->yearsInCompany);
				}
				else if (i == 11){
					sscanf(token,"%d",&newLine->workAccident);
				}
				else if (i == 12){
					sscanf(token,"%d",&newLine->promotionsLast5Years);
				}
				token = strtok(NULL, "\t");
				i = i + 1;
			}

			numMatches++;

			/*
            sscanf(temp,"%d\t%s\t%s\t%lf\t%lf\t%lf\t%s\t%f\t%d\t%d\t%d\t%d\t%d\n",
            &newLine->id,newLine->employeeName,newLine->jobTitle,&newLine->basePay,&newLine->overtimePay,
            &newLine->benefit,newLine->status,&newLine->satisfactionLevel,&newLine->numberProject,
            &newLine->averageMonthlyHours,&newLine->yearsInCompany,&newLine->workAccident,&newLine->promotionsLast5Years);
            numMatches++;
			*/
        }
        line_num++;
    }
    if (numMatches == 0) // no results found
    {
        printf("\nQuery does not exist in history file...forwarding request to server.\n");
    }
    if (f)
    {
        fclose(f); //Close the file if still open.
    }
    return numMatches; 
}

int writeFile(char *fname, struct EmployeeStructure newLine, int writePos){
    FILE *fp;
    FILE *fp2;
    char tempFName[] = "HistoryTemp.c";
    char temp[512];
    int write = 0;
    int i = 0;
    int writePosition = writePos;

    //printf("Writing File.");

    if ((fp = fopen(fname, "r")) == NULL){
        return (-1);
    }

    if ((fp2 = fopen(tempFName, "w")) == NULL){
        return(-1);
    }

	convertToLowerCase(newLine.employeeName);
	convertToLowerCase(newLine.jobTitle);
	convertToLowerCase(newLine.status);

    while(fgets(temp,512,fp) != NULL){
        //printf("%d == %d ", i, writePosition);
        if (i == writePosition && write == 0){
            //printf("New Line In");
            fprintf(fp2,"%d\t%s\t%s\t%f\t%f\t%f\t%s\t%f\t%d\t%d\t%d\t%d\t%d\n",
            newLine.id,newLine.employeeName,newLine.jobTitle,newLine.basePay,newLine.overtimePay,
            newLine.benefit,newLine.status,newLine.satisfactionLevel,newLine.numberProject,
            newLine.averageMonthlyHours,newLine.yearsInCompany,newLine.workAccident,newLine.promotionsLast5Years);
            write = 1;
        }
        else{
            fprintf(fp2,"%s", temp);
        }
        i = i+1;
    }
    if (write == 0){
        //printf("New Line In");
        fprintf(fp2,"%d\t%s\t%s\t%f\t%f\t%f\t%s\t%f\t%d\t%d\t%d\t%d\t%d\n",
        newLine.id,newLine.employeeName,newLine.jobTitle,newLine.basePay,newLine.overtimePay,
        newLine.benefit,newLine.status,newLine.satisfactionLevel,newLine.numberProject,
        newLine.averageMonthlyHours,newLine.yearsInCompany,newLine.workAccident,newLine.promotionsLast5Years);
        write = 1;
    }
    fclose(fp2);
    fclose(fp);
    remove(fname);
    rename("HistoryTemp.c",fname);
	sleep(1);
    return 0;
};

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
			// convertToLowerCase(test->status);
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