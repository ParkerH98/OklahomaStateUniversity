#include <stdio.h>
#include <stdlib.h>

void historyFile(char* fileName, char* employeeInfo){
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
			printf("%c", newLine);
			fprintf(temp, "%c", newLine);
		}
		fputs(employeeInfo, temp);
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
}

int main(){
	return 0;
}
