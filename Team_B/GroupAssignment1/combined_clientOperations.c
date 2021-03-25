#include "header.h"
// #include <sys/socket.h>
// #include <netinet/in.h>
// #define PORT 9004


// int inet_addr();

// =======================================================================
// CLIENT CONNECTION FUCNTIONS
// =======================================================================
void forwardQueryToServer(char *employeeName, char *jobTitle, char *status)
{
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    // The three arguments are: Internet domain, Stream socket, Default protocol (TCP in this case)
    clientSocket = socket(PF_INET, SOCK_STREAM, 0); // Create the socket
    if (clientSocket < 0) { perror("[-]Error in socket"); exit(1); }
    // printf("[+]Server socket created successfully.\n");

    // Configure settings of the server address struct
    serverAddr.sin_family = AF_INET; //Address family = Internet
    serverAddr.sin_port = htons(PORT); //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //Set IP address to localhost
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    // Connect the socket to the server using the address struct
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *)&serverAddr, addr_size);
    if (clientSocket == -1) { perror("[-]Error in socket"); exit(1); }
    // printf("[+]Connected to Server.\n\n");

    //=======================================
    // SENDING AND RECEIVING AFTER THIS POINT
    //=======================================

    struct Query query;
    struct Query *queryPtr = &query;

    // assigns input data to Query struct
    strcpy(queryPtr->employeeName, employeeName);
    strcpy(queryPtr->jobTitle, jobTitle);
    strcpy(queryPtr->status, status);

    send(clientSocket, queryPtr, sizeof(struct Query), 0);
    printf("CLIENT: Query sent to server.\n\n");


    struct EmployeeStructure employee;
    struct EmployeeStructure *employeePtr = &employee;

    read(clientSocket, employeePtr , sizeof(struct EmployeeStructure));

    printf("CLIENT: Result received from server.\n");
    printf("Id: %d\n", employeePtr->id);
    printf("Employee Name: %s\n", employeePtr->employeeName);
    printf("Job Title: %s\n", employeePtr->jobTitle);
    printf("Base Pay: %f\n", employeePtr->basePay);
    printf("Overtime Pay: %f\n", employeePtr->overtimePay);
    printf("Benefit: %f\n", employeePtr->benefit);
    printf("Status: %s\n", employeePtr->status);
    printf("Satisfaction Level: %f\n", employeePtr->satisfactionLevel);
    printf("Number of Projects: %d\n", employeePtr->numberProject);
    printf("Average Monthly Hours: %d\n", employeePtr->averageMonthlyHours);
    printf("Company Time (Years): %d\n", employeePtr->yearsInCompany);
    printf("Work Accident: %d\n", employeePtr->workAccident);
    printf("Promotion in Last 5 Years: %d\n", employeePtr->promotionsLast5Years);

    // printToTerminal(employeePtr);

    close(clientSocket);
}


void receiveQueryFromAssistant(struct Query query)
{
    int entrySocket, connectionSocket; // socket file descriptors
    int bindCheck;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    // The three arguments are: Internet domain, Stream socket, Default protocol (TCP in this case)
    entrySocket = socket(PF_INET, SOCK_STREAM, 0); // Create the socket

    // Configure settings of the server address struct
    serverAddr.sin_family = AF_INET;                               //Address family = Internet
    serverAddr.sin_port = htons(PORT);                             //Set port number, using htons function to use proper byte order
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");           //Set IP address to localhost
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //Set all bits of the padding field to 0

    bindCheck = bind(entrySocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)); //Bind the address struct to the socket
    if (bindCheck < 0) { perror("[-]Error in bind"); exit(1); }
    // printf("[+]Binding successfull.\n");

    // Listen on the socket, with 5 max connection requests queued
    if (listen(entrySocket, 5) == 0) { printf("SERVER: Listening....\n"); }
    else { printf("[-]Error in listening"); }

    for (int i = 0; i < TESTING_LOOP; i++)
    {
        // Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;
        connectionSocket = accept(entrySocket, (struct sockaddr *)&serverStorage, &addr_size);

        //=======================================
        // SENDING AND RECEIVING AFTER THIS POINT
        //=======================================


        struct Query *queryPtr = &query;

        recv(connectionSocket, queryPtr, sizeof(struct Query), 0); //Read the message from the server into the buffer
        printf("SERVER: Query received from assistant:\n\n%s\n%s\n%s\n", queryPtr->employeeName, queryPtr->jobTitle, queryPtr->status); //Print the received message

        struct EmployeeStructure employee;
        struct EmployeeStructure *employeePtr = &employee;

        // employeePtr->id = 15000;
        // strcpy(employeePtr->employeeName, "BRIAN BENSON");
        // strcpy(employeePtr->jobTitle, "IS BUSINESS ANALYST");
        // employeePtr->basePay = 78059.8;
        // employeePtr->overtimePay = 0;
        // employeePtr->benefit = 0;
        // strcpy(employeePtr->status, "FT");
        // employeePtr->satisfactionLevel = 0.37;
        // employeePtr->numberProject = 2;
        // employeePtr->averageMonthlyHours = 158;
        // employeePtr->yearsInCompany = 3;
        // employeePtr->workAccident = 0;
        // employeePtr->promotionsLast5Years = 0;

        // send(connectionSocket, employeePtr, sizeof(struct EmployeeStructure), 0);
        printf("\nSERVER: Result sent to assistant.\n\n");
    }
    close(entrySocket);
}



















void sendQueryAndGetEmployeeStruct(struct Query query, struct EmployeeStructure *employeeStruct)
{
 
    struct Query* pQuery = &query;
    struct EmployeeStructure* pEmployeeStruct = employeeStruct;
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
    valread = read( sock , pEmployeeStruct, sizeof(pEmployeeStruct)+STATUS_LEN+JOBTITLE_LEN+EMPLOYEENAME_LEN +sizeof(int)*7+sizeof(double)*3+sizeof(float)); 
    
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

    
    // printf("To exit Server, Press Control + c \n");
}
