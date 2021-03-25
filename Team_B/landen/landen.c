#include <stdio.h>
#include <stdlib.h>

void historyFile(char* fileName, struct EmployeeStructure employee){
//Accepts the name of the file as a string and the employee's information as a string for arguments.
	
	FILE *history;
	history = fopen(fileName, "r");  //Opens the history file
	
	FILE *temp;
	temp = fopen("temp.txt", "w+");  //Creates a new file to copy the old history file to
	
	char newLine;
	int count = 0;
	
	
	while((newLine = getc(history)) != EOF){
		if(newLine == '\n'){
			count++;  //Whenever the char variable newLine is a newline character, int variable count increments by one. This is done to check whether or not the file has 10 lines.
		}
	}
	
	fseek(history, 0, SEEK_SET);
	
	if(count < 10){
		while((newLine = getc(history)) != EOF){
			fprintf(temp, "%c", newLine);
		}
		fprintf(temp, "Id: %d ", employee.id);
		fprintf(temp, "Employee Name: %s ", employee.employeeName);
		fprintf(temp, "Job Title: %s ", employee.jobTitle);
		fprintf(temp, "Base Pay: %f ", employee.basePay);
		fprintf(temp, "Overtime Pay: %f ", employee.basePay);
		fprintf(temp, "Benefit: %f ", employee.benefit);
		fprintf(temp, "Status: %s ", employee.status);
		fprintf(temp, "Satisfaction Level: %f ", employee.satisfactionLevel);
		fprintf(temp, "Number of Projects: %d ", employee.numberProject);
		fprintf(temp, "Average Monthly Hours: %d ", employee.employee.averageMonthlyHours);
		fprintf(temp, "Company Time (Years): %d ", employee.yearsInCompany);
		fprintf(temp, "Work Accident: %d ", employee.workAccident);
		fprintf(temp, "Promotion in Last 5 Years: %d\n", employee.promotionsLast5Years);
		//If the history file has less than 10 lines, the whole history file is copied to temp, and then the new employee information is appended to the end.
	}
	else{
		int tmpcount = 0;
		while((newLine = getc(history)) != EOF){
			if(tmpcount > 0){
				fprintf(temp, "%c", newLine);
			}
			if(newLine == '\n'){
				tmpcount++;
			}
		}
		fputs(employeeInfo, temp);
		//If the history file already has 10 lines, all of the employee info except for the first line is copied to temp, then the new employee information is appended to the end.
	}
	
	fclose(history); //Closes the history file
	remove(fileName); //Deletes the history file
	fclose(temp); //Closes temp
	rename("temp.txt", fileName); //Renames temp to the same name as the history file
	return;
}

int main(){
	return 0;
}
	
// printf("Id: %d\n", employee.id);
// printf("Employee Name: %s\n", employee.employeeName);
// printf("Job Title: %s\n", employee.jobTitle);
// printf("Base Pay: %f\n", employee.basePay);
// printf("Overtime Pay: %f\n", employee.overtimePay);
// printf("Benefit: %f\n", employee.benefit);
// printf("Status: %s\n", employee.status);
// printf("Satisfaction Level: %f\n", employee.satisfactionLevel);
// printf("Number of Projects: %d\n", employee.numberProject);
// printf("Average Monthly Hours: %d\n", employee.averageMonthlyHours);
// printf("Company Time (Years): %d\n", employee.yearsInCompany);
// printf("Work Accident: %d\n", employee.workAccident);
// printf("Promotion in Last 5 Years: %d\n", employee.promotionsLast5Years);
// printf("Should display in a new window\n"); // tests that stdout prints to new terminal
// printf("===================================================\n\n");
