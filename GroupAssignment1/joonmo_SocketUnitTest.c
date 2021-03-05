#include "header.h"
#include <sys/wait.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 

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

    pid_t pid;	//The pid_t data type is a signed integer type which is capable of 					representing a process ID.
	
	/* fork a child process */
	pid = fork();

	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if (pid == 0) { /* child process */
		struct employeeStructure employeeStruct;
        struct employeeStructure* pEmployeeStruct = &employeeStruct;
        int server_fd, new_socket, valread;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        // char buffer[1024] = {0}; 
        char *hello = "Hello from server"; 
        
        // Creating socket file descriptor 
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
        {
            perror("socket failed");
            return -1;
        }
        
        // Forcefully attaching socket to the port 8080 
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                    &opt, sizeof(opt))) 
        { 
            perror("setsockopt"); 
            return -1; 
        }
        address.sin_family = AF_INET; 
        address.sin_addr.s_addr = INADDR_ANY; 
        address.sin_port = htons( PORT ); 
        

        // Forcefully attaching socket to the port 8080 
        if (bind(server_fd, (struct sockaddr *)&address,  
                                    sizeof(address))<0) 
        { 
            perror("bind failed"); 
            return -1;
        } 
        if (listen(server_fd, 3) < 0) 
        { 
            perror("listen"); 
            return -1; 
        } 
        
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                        (socklen_t*)&addrlen))<0) 
        { 
            perror("accept");
            return -1;
        } 
        valread = read( new_socket , pEmployeeStruct, 130+sizeof(int)*7+sizeof(float)*4);
        // char name[20];
        // char name2[20];
        // int age = 0;
        // age = pSample->age;


    

        char employeeName[30];
        char jobTitle[50];
        char status[50];


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
        send(new_socket , hello , strlen(hello) , 0 ); 
        printf("Hello message sent\n"); 
        printf("The child process is done!\n");
	}
	else { /* parent process */
        sleep(2);
		/* parent will wait for the child to complete */
        struct employeeStructure employeeStructClient;
        employeeStructClient.id = 1;
        strcpy(employeeStructClient.employeeName, "NATHANIEL FORD");
        strcpy(employeeStructClient.jobTitle, "GENERAL MANAGER-METROPOLITAN TRANSIT AUTHORITY");
        employeeStructClient.basePay = 167411.18;
        employeeStructClient.overtimePay = 0;
        employeeStructClient.benefit = 400184.25;
        strcpy(employeeStructClient.status, "PT");
        employeeStructClient.satisfactionLevel =0.38;
        employeeStructClient.numberProject = 2;
        employeeStructClient.averageMonthlyHours = 157;
        employeeStructClient.yearsInCompany = 3;
        employeeStructClient.workAccident =0;
        employeeStructClient.promotionsLast5Years =1;
        employeeStructClient.duplicateExists = 0;
    

        // sample.yourName = "Koo";
        struct employeeStructure* pEmployeeStructClient = &employeeStructClient;

        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char *hello = "Hello from client"; 
        char buffer[1024] = {0}; 

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
        
        // send(sock , hello , strlen(hello) , 0 ); 
        send(sock , pEmployeeStructClient, 130+sizeof(int)*7+sizeof(float)*4 , 0 );
        printf("Hello message sent\n"); 
        valread = read( sock , buffer, 1024); 
        printf("%s\n",buffer );





		wait(NULL);
		printf("Parent Process Complete\n");
	}
	return 0;
}