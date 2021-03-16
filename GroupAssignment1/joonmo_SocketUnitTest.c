


#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <string.h> 
#include "header.h"
#define PORT 8080 


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





int main() {    
    /*
    This is For Server-Client Sockect Testing
    Client send Quary to Server
    Server recived Quary, and send employee Structure 
    loop for sending query multiple times. It set 2 times
    */
    pid_t pid;	//The pid_t data type is a signed integer type which is capable of 					representing a process ID.
	
	/* fork a child process */
	pid = fork();

	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if (pid == 0) { 
        sleep(1);

        /* Client process */

        // ===================Socket Client Setup START===================
        struct Query query;
        struct Query* pQuery = &query;
        strcpy(query.employeeName, "NATHANIEL FORD");
        strcpy(query.jobTitle, "GENERAL MANAGER-METROPOLITAN TRANSIT AUTHORITY");
        strcpy(query.status, "PT");

        struct employeeStructure employeeStruct;
        struct employeeStructure* pEmployeeStruct = &employeeStruct;
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        // char *hello = "Hello from client"; 
        char buffer[1024] = {0}; 


        int loopForClientSocket = 1;
        int counter = 2;
        // This is loop for sending query multiple times. It set 2 times
        while (loopForClientSocket){
            if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
            { 
                printf("\n Socket creation error \n"); 
                return -1; 
            } 

            serv_addr.sin_family = AF_INET; 
            serv_addr.sin_port = htons(PORT); 
                
            // Convert IPv4 and IPv6 addresses from text to binary form 
            if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
            { 
                printf("\nInvalid address/ Address not supported \n"); 
                return -1; 
            } 
        
            if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
            { 
                printf("\nConnection Failed \n"); 
                return -1; 
            }
            // ===================Socket Client Setup END===================



        

            // ==================Socket Clinet Operations START==================
            send(sock , pQuery, sizeof(pQuery)+ EMPLOYEENAME_LEN + JOBTITLE_LEN + STATUS_LEN, 0 ); 
            // send(sock , hello , strlen(hello) , 0 ); 
            printf("Query sent from Client\n"); 


            while (read( sock , pEmployeeStruct, 130+sizeof(int)*7+sizeof(float)*4) == -1){
                printf("Client Waiting");
            }
            // valread = read( sock , pEmployeeStruct, 130+sizeof(int)*7+sizeof(float)*4); 
            char employeeName[30];
            char jobTitle[50];
            char status[50];
            printf("======Client Recived employee Sturct======\n");
            printf("%d\n", pEmployeeStruct->id);
            strcpy(employeeName, pEmployeeStruct->employeeName);
            printf("%s\n",employeeName);
            strcpy(jobTitle, pEmployeeStruct->jobTitle);
            printf("%s\n",jobTitle);
            printf("%f\n", pEmployeeStruct->overtimePay);
            printf("%f\n", pEmployeeStruct->basePay);
            printf("%f\n", pEmployeeStruct->benefit);
            strcpy(status, pEmployeeStruct->status);
            printf("%s\n",status);
            printf("%f\n", pEmployeeStruct->satisfactionLevel);
            printf("%d\n", pEmployeeStruct->numberProject); 
            printf("%d\n", pEmployeeStruct->averageMonthlyHours);
            printf("%d\n", pEmployeeStruct->yearsInCompany);
            printf("%d\n", pEmployeeStruct->workAccident);
            printf("%d\n", pEmployeeStruct->promotionsLast5Years);
            printf("%d\n", pEmployeeStruct->duplicateExists);
            printf("==========================================\n");
            
            counter--;
            close(sock);
            if (counter == 0){
                break;
            }
        }
        //==================Socket Clinet Operation END==================

        printf("The Client process is done!\n");
        printf("To exit Server, Press Control + c \n");
	}
	else {
        
         /* Server process */
        
        
        struct employeeStructure employeeStruct;
        struct employeeStructure* pEmployeeStruct = &employeeStruct;

        // ===================Testing Info===================
        employeeStruct.id = 1;
        strcpy(employeeStruct.employeeName, "NATHANIEL FORD");
        strcpy(employeeStruct.jobTitle, "GENERAL MANAGER-METROPOLITAN TRANSIT AUTHORITY");
        employeeStruct.basePay = 167411.18;
        employeeStruct.overtimePay = 0;
        employeeStruct.benefit = 400184.25;
        strcpy(employeeStruct.status, "PT");
        employeeStruct.satisfactionLevel =0.38;
        employeeStruct.numberProject = 2;
        employeeStruct.averageMonthlyHours = 157;
        employeeStruct.yearsInCompany = 3;
        employeeStruct.workAccident =0;
        employeeStruct.promotionsLast5Years =1;
        employeeStruct.duplicateExists = 0;
        // =========================================================

        // ===================Socket Server Setup START===================
        struct Query query;
        struct Query* pQuery = &query;
        int server_fd, new_socket, valread, quaryRead;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        char buffer[1024] = {0}; 
        char *hello = "Hello from server"; 
        // Creating socket file descriptor 
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }
        // Forcefully attaching socket to the port 8080 
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                    &opt, sizeof(opt))) 
        { 
            perror("setsockopt"); 
            exit(EXIT_FAILURE); 
        }
        address.sin_family = AF_INET; 
        address.sin_addr.s_addr = INADDR_ANY; 
        address.sin_port = htons( PORT ); 
        // Forcefully attaching socket to the port 8080 
        if (bind(server_fd, (struct sockaddr *)&address,  
                                    sizeof(address))<0) 
        { 
            perror("bind failed"); 
            exit(EXIT_FAILURE);
        } 
        if (listen(server_fd, 3) < 0) 
        { 
            perror("listen"); 
            exit(EXIT_FAILURE); 
        } 
         // ==================Socket Server Setup END===================

        // ==================Socket Operation START==================
        int loopGoing = 1;
        while(loopGoing){
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                            (socklen_t*)&addrlen))<0) 
            { 
                perror("accept");
                exit(EXIT_FAILURE);
            } 

            quaryRead = read( new_socket , pQuery, sizeof(pQuery)+ EMPLOYEENAME_LEN + JOBTITLE_LEN + STATUS_LEN);
            
            // valread = read( new_socket , buffer, 1024);
            printf("%s\n",buffer );
            printf("Server Recived Query employeeName ========= %s\n",pQuery->employeeName);
            printf("Server Recived Query jobTitle ============= %s\n",pQuery->jobTitle);
            printf("Server Recived Query status =============== %s\n",pQuery->status);
            // printf("To exit Server, Press Control + c \n");
            printf("Server is Working for 10 sec. Client should wait\n");
            sleep(10);
            send(new_socket , pEmployeeStruct, 130+sizeof(int)*7+sizeof(float)*4 , 0 );
            printf("empolyee structure is sent from Server\n"); 


           
            // send(new_socket , hello , strlen(hello) , 0 ); 
            
        }
		// ==================Socket Operation END==================
		
        wait(NULL);
        printf("Server Process is Done!\n");
	}
	return 0;
}