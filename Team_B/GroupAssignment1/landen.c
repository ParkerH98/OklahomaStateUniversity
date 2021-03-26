#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

void writeToHistoryFile(char* fileName, struct EmployeeStructure employee){
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
		fprintf(temp, "Id: [%d] ", employee.id);
		fprintf(temp, "Employee Name: {%s} ", employee.employeeName);
		fprintf(temp, "Job Title: <%s>  ", employee.jobTitle);
		fprintf(temp, "Base Pay: [%f]  ", employee.basePay);
		fprintf(temp, "Overtime Pay: [%f]  ", employee.basePay);
		fprintf(temp, "Benefit: [%f]  ", employee.benefit);
		fprintf(temp, "Status: /%s/ ", employee.status);
		fprintf(temp, "Satisfaction Level: [%f]  ", employee.satisfactionLevel);
		fprintf(temp, "Number of Projects: [%d]  ", employee.numberProject);
		fprintf(temp, "Average Monthly Hours: [%d]  ", employee.averageMonthlyHours);
		fprintf(temp, "Company Time (Years): [%d]  ", employee.yearsInCompany);
		fprintf(temp, "Work Accident: [%d]  ", employee.workAccident);
		fprintf(temp, "Promotion in Last 5 Years: [%d]\n", employee.promotionsLast5Years);
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
		
		fprintf(temp, "Id: [%d] ", employee.id);
		fprintf(temp, "Employee Name: {%s} ", employee.employeeName);
		fprintf(temp, "Job Title: <%s> ", employee.jobTitle);
		fprintf(temp, "Base Pay: [%f] ", employee.basePay);
		fprintf(temp, "Overtime Pay: [%f] ", employee.basePay);
		fprintf(temp, "Benefit: [%f] ", employee.benefit);
		fprintf(temp, "Status: /%s/ ", employee.status);
		fprintf(temp, "Satisfaction Level: [%f] ", employee.satisfactionLevel);
		fprintf(temp, "Number of Projects: [%d] ", employee.numberProject);
		fprintf(temp, "Average Monthly Hours: [%d] ", employee.averageMonthlyHours);
		fprintf(temp, "Company Time (Years): [%d] ", employee.yearsInCompany);
		fprintf(temp, "Work Accident: [%d] ", employee.workAccident);
		fprintf(temp, "Promotion in Last 5 Years: [%d]\n", employee.promotionsLast5Years);
		//If the history file already has 10 lines, all of the employee info except for the first line is copied to temp, then the new employee information is appended to the end.
	}
	
	fclose(history); //Closes the history file
	remove(fileName); //Deletes the history file
	fclose(temp); //Closes temp
	rename("temp.txt", fileName); //Renames temp to the same name as the history file
	return;
}

struct EmployeeStructure getEmployeeFromHistory(char* fileName, struct Query query){
	
	struct EmployeeStructure employee;
	
	FILE *history;
	history = fopen(fileName, "r");
	
	char *name = query.employeeName;
	char *jobTitle = query.jobTitle;
	char *status = query.status;
	
	char idString[500];
	int id;
	
	char basePayString[500];
	double basePay;
	
	char overtimePayString[500];
	double overtimePay;
	
	char benefitString[500];
	double benefit;
	
	char satisfactionLevelString[500];
	float satisfactionLevel;
	
	char numberProjectString[500];
	int numberProject;
	
	char averageMonthlyHoursString[500];
	int averageMonthlyHours;
	
	char yearsInCompanyString[500];
	int yearsInCompany;
	
	char workAccidentString[500];
	int workAccident;
	
	char promotionsLast5YearsString[500];
	int promotionsLast5Years;
	
	char next;
	
	bool sameName = true;
	bool sameJobTitle = true;
	bool sameStatus = true;
	
	while((next = getc(history)) != EOF){
		
		if(next == '{'){
			int i = 0;
			while((next = getc(history)) != '}'){
				if(next != name[i]){
					sameName = false;
				}
				i++;
			}
		}
		
		if(next == '<'){
			int i = 0;
			while((next = getc(history)) != '>'){
				if(next != jobTitle[i]){
					sameJobTitle = false;
				}
				i++;
			}
		}
		
		if(next == '/'){
			int i = 0;
			while((next = getc(history)) != '/'){
				if(next != status[i]){
					sameStatus = false;
				}
				i++;
			}
		}
	}
	
	fseek(history, 0, SEEK_SET);
	
	if(sameName && sameJobTitle && sameStatus){
		
		int i = 0;
		
		strcpy(employee.employeeName, name);
		strcpy(employee.jobTitle, jobTitle);
		strcpy(employee.status, status);
		
		while((next = getc(history)) != EOF){
			if(next == '[' && i == 0){
				i++;
				int j = 0;
				while((next = getc(history)) != ']'){
					idString[j] = next;
					j++;
				}
			}
			else if(next == '[' && i == 1){
				i++;
				int j = 0;
				while((next = getc(history)) != ']'){
					basePayString[j] = next;
					j++;
				}
			}
			else if(next == '[' && i == 2){
				i++;
				int j = 0;
				while((next = getc(history)) != ']'){
					overtimePayString[j] = next;
					j++;
				}
			}
			else if(next == '[' && i == 3){
				i++;
				int j = 0;
				while((next = getc(history)) != ']'){
					benefitString[j] = next;
					j++;
				}
			}
			else if(next == '[' && i == 4){
				i++;
				int j = 0;
				while((next = getc(history)) != ']'){
					satisfactionLevelString[j] = next;
					j++;
				}
			}
			else if(next == '[' && i == 5){
				i++;
				int j = 0;
				while((next = getc(history)) != ']'){
					numberProjectString[j] = next;
					j++;
				}
			}
			else if(next == '[' && i == 6){
				i++;
				int j = 0;
				while((next = getc(history)) != ']'){
					averageMonthlyHoursString[j] = next;
					j++;
				}
			}
			else if(next == '[' && i == 7){
				i++;
				int j = 0;
				while((next = getc(history)) != ']'){
					yearsInCompanyString[j] = next;
					j++;
				}
			}
			else if(next == '[' && i == 8){
				i++;
				int j = 0;
				while((next = getc(history)) != ']'){
					workAccidentString[j] = next;
					j++;
				}
			}
			else if(next == '[' && i == 9){
				i++;
				int j = 0;
				while((next = getc(history)) != ']'){
					promotionsLast5YearsString[j] = next;
					j++;
				}
			}
		}
		
		char *end;
		
		id = atoi(idString);
		employee.id = id;
		
		basePay = strtod(basePayString, &end);
		employee.basePay = basePay;
		
		overtimePay = strtod(overtimePayString, &end);
		employee.overtimePay = overtimePay;
		
		benefit = strtod(benefitString, &end);
		employee.benefit = benefit;
		
		satisfactionLevel = strtof(satisfactionLevelString, &end);
		employee.satisfactionLevel = satisfactionLevel;
		
		numberProject = atoi(numberProjectString);
		employee.numberProject = numberProject;
		
		averageMonthlyHours = atoi(averageMonthlyHoursString);
		employee.averageMonthlyHours = averageMonthlyHours;
		
		yearsInCompany = atoi(yearsInCompanyString);
		employee.yearsInCompany = yearsInCompany;
		
		workAccident = atoi(workAccidentString);
		employee.workAccident = workAccident;
		
		promotionsLast5Years = atoi(promotionsLast5YearsString);
		employee.promotionsLast5Years = promotionsLast5Years;
	}
	
	fclose(history);
	
	return employee;
}

// gcc landen.c 
// int main(){
// 	struct EmployeeStructure employee;
// 	employee.id = 15000;
// 	strcpy(employee.employeeName, "BRIAN BENSON");
// 	strcpy(employee.jobTitle, "IS BUSINESS ANALYST");
// 	employee.basePay = 78059.8;
// 	employee.overtimePay = 0;
// 	employee.benefit = 0;
// 	strcpy(employee.status, "FT");
// 	employee.satisfactionLevel = 0.37;
// 	employee.numberProject = 2;
// 	employee.averageMonthlyHours = 158;
// 	employee.yearsInCompany = 3;
// 	employee.workAccident = 0;
// 	employee.promotionsLast5Years = 0;

// 	writeToHistoryFile("history.txt", employee);
// 	return 0;
// }
	
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
