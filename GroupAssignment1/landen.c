#include <stdio.h>
#include <stdlib.h>

void historyFile(char* fileName, char* employeeInfo){

	FILE *history;
	fopen(fileName, "r+");

	char newLine;
	
	char lines[10][500];
	
	int i = 9;
	while((newLine = getc(history)) != EOF){
		int j = 0;
		if(newLine == '\n'){
			i--;
		}
		else{
			lines[i][j] = newLine;
			j++;
		}
	}
	
	for(int h = 9; h >= 0; h--){
		for(int k = 0; k < 500; k++){
			lines[h][k] = lines[h - 1][k];
		}
	}
	for(int k = 0; k < 500; k++){
		lines[0][k] = employeeInfo[k];
	}
	
	return;
}

int main(){
	return 0;
}
