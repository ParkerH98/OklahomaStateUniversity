#include <stdio.h>
#include <stdlib.h>

void historyFile(char* fileName, char* employeeInfo){
FILE *history;
	history = fopen(fileName, "r");
	
	FILE *temp;
	temp = fopen("temp.txt", "w+");
	
	char newLine;
	
	int count = 0;
	
	while((newLine = getc(history)) != EOF){
		if(newLine == '\n'){
			count++;
		}
	}
	
	if(count < 10){
		while((newLine = getc(history)) != EOF){
			fputs(newLine, temp);
		}
		fputs(employeeInfo, temp);
	}
	else{
		tmpcount = 0;
		while((newLine = getc(history)) != EOF){
			if(tmpcount > 0){
				fputs(newLine, temp);
			}
			if(newLine == '\n'){
				tmpcount++;
			}
		}
		fputs(employeeInfo, temp);
	}
	
	fclose(history);
	remove(fileName);
	rename("temp.txt", fileName);
	fclose(temp);
	return;
}

int main(){
	return 0;
}
