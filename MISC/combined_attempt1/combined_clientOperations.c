#include "header.h"
// #include <sys/socket.h>
// #include <netinet/in.h>
// #define PORT 9004


// int inet_addr();

// =======================================================================
// CLIENT CONNECTION FUCNTIONS
// =======================================================================

void sendQueryAndGetEmployeeStruct(struct Query query, struct EmployeeStructure employeeStruct)
{
 
    struct Query* pQuery = &query;
    struct EmployeeStructure* pEmployeeStruct = &employeeStruct;
    // strcpy(query.employeeName, "THOMAS SMITH");
	// strcpy(query.jobTitle, "SPECIAL NURSE");
	// strcpy(query.status, "FT");


    // struct employeeStructure employeeStruct;
    // struct employeeStructure* pEmployeeStruct = &employeeStruct;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    // char *hello = "Hello from client"; 
    // char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        // return -1; 
    } 

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
        
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        // return -1; 
    } 

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        // return -1; 
    }
    // ===================Socket Client Setup END===================





    // ==================Socket Clinet Operations START==================
    send(sock , pQuery, sizeof(pQuery)+ EMPLOYEENAME_LEN + JOBTITLE_LEN + STATUS_LEN, 0 ); 
    // send(sock , hello , strlen(hello) , 0 ); 
    printf("Client sent Query\n"); 
    // printf("\n====================\nQUERY END\n====================\n\n");

    // while (read( sock , pEmployeeStruct, 130+sizeof(int)*7+sizeof(float)*4) == 0){
    //     printf("Client Waiting");
    // }
    valread = read( sock , pEmployeeStruct, sizeof(pEmployeeStruct)+ EMPLOYEENAME_LEN + JOBTITLE_LEN + STATUS_LEN +sizeof(int)*7+sizeof(float)*4); 
    
    char employeeName[EMPLOYEENAME_LEN];
    char jobTitle[JOBTITLE_LEN];
    char status[STATUS_LEN];
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
    
    close(sock);
        
    
    //==================Socket Clinet Operation END==================

    printf("The Client process is done!\n");
    printf("To exit Server, Press Control + c \n");
}
