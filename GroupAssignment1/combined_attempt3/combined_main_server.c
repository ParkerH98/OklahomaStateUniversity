#include "header.h"
#include <sys/socket.h>
// #include <netinet/in.h>


// int inet_addr();


// Run: gcc combined_main_server.c -lpthread -o server




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

struct EmployeeStack* searchMain(void *sourceQueryFromClient){
    struct Query* queryFromClient = sourceQueryFromClient;
	struct EmployeeStructure* pEmployeeStruct = malloc(sizeof (struct EmployeeStructure)); //Introduced by M Oliver.
    // NOTE: Yes, I'm aware that this is now implemented as a queue. It would take too long to fix.
    // Generate the first item in the Stack of Employee Objects, put in the last of list value, and attach the head to the same location.
    struct EmployeeStack *bottom = malloc(sizeof (struct EmployeeStack));
    bottom->data.id = -99;
    struct EmployeeStack *top = bottom;
    // Generate the first "blank" EmployeeQueue.
    struct EmployeeStack *temp = malloc(sizeof (struct EmployeeStack));
    temp->data.id = -100;


	FILE *fp;
    char buff[255];

    // Open File
    fp = fopen("inputTxtFiles/Name.txt", "r");
    // For every line in the file.
    while (fgets(buff, sizeof(buff), fp)) {
        //Grab the Employee Name and ID.
        char * employeeIDString = strtok(buff, "\t");
		int employeeID = atoi(employeeIDString);
        char * employeeName = strtok(NULL, "");
        //Clean up the terminal character. on name
        if (employeeName[strlen(employeeName)-1] == '\n'){
            employeeName[strlen(employeeName)-1] = 0;
        }
        //If the Name we have is the name we're looking for.
		if(strcmp(employeeName, queryFromClient->employeeName) == 0){
            // Load the ID and Name into the Employee Structure at pEmployeeStruct.
            strcpy(pEmployeeStruct->employeeName, employeeName);
            pEmployeeStruct->id = employeeID;

            // Then we send it off into ThreadSpawn to get the rest of that field.
            ThreadSpawn(pEmployeeStruct);
            // If it's a match,
            if (strcmp(pEmployeeStruct->status, queryFromClient->status) == 0 && 
                strcmp(pEmployeeStruct->jobTitle, queryFromClient->jobTitle) == 0){

                // we load it into a EmployeeQueue Object.
                temp->data.id = pEmployeeStruct->id;
                strcpy(temp->data.employeeName, pEmployeeStruct->employeeName);
                temp->data.benefit = pEmployeeStruct->benefit;
                strcpy(temp->data.jobTitle, pEmployeeStruct->jobTitle); 
                temp->data.numberProject = pEmployeeStruct->numberProject;
                temp->data.averageMonthlyHours = pEmployeeStruct->averageMonthlyHours;
                temp->data.basePay = pEmployeeStruct->basePay;
                temp->data.overtimePay = pEmployeeStruct->overtimePay;
                temp->data.promotionsLast5Years = pEmployeeStruct->promotionsLast5Years;
                temp->data.satisfactionLevel = pEmployeeStruct->satisfactionLevel;
                strcpy(temp->data.status, pEmployeeStruct->status);
                temp->data.workAccident = pEmployeeStruct->workAccident;
                temp->data.yearsInCompany = pEmployeeStruct->yearsInCompany;

                // Then we attach the next field to the old top of the stack.
                temp->next = top;
                // and update the top of the stack.
                top = temp;

                // Now that we have the new item firmly on the stack, where we can't lose track of it,
                // we allocate temp to a new field.
                temp = malloc(sizeof (struct EmployeeStack));
            }
            /*
            // Otherwise, release the information, and reallocate the dynamic memory.
            else{
                free(pEmployeeStruct);
                pEmployeeStruct = malloc(sizeof *pEmployeeStruct);
            }
            */

        }
    }
    // Once we're done, we release the file pointer.
    fclose(fp);

    // Then we release the Employee Structure.
    free(pEmployeeStruct);
    
    // If temp never had a new ID put in it (no matches found at all), we free temp.
    // Otherwise, temp points at the same place as top.
    if (temp->data.id == -100){
        free(temp);
    }

    return top;

}

// server
void main(){
    int entrySocket, connectionSocket; // socket file descriptors
    int bindCheck;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    struct EmployeeStack *top;

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

    while (1)
    {
        // Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;
        connectionSocket = accept(entrySocket, (struct sockaddr *)&serverStorage, &addr_size);

        //=======================================
        // SENDING AND RECEIVING AFTER THIS POINT
        //=======================================

        struct Query query;
        struct Query *queryPtr = &query;

        recv(connectionSocket, queryPtr, sizeof(queryPtr)+ EMPLOYEENAME_LEN + JOBTITLE_LEN + STATUS_LEN, 0); //Read the message from the server into the buffer
        printf("SERVER: Query received from assistant:\n\n%s\n%s\n%s\n", queryPtr->employeeName, queryPtr->jobTitle, queryPtr->status); //Print the received message

        struct EmployeeStructure employee;
        struct EmployeeStructure *employeePtr = &employee;

        /*
        employeePtr->id = 15000;
        strcpy(employeePtr->employeeName, "BRIAN BENSON");
        strcpy(employeePtr->jobTitle, "IS BUSINESS ANALYST");
        employeePtr->basePay = 78059.8;
        employeePtr->overtimePay = 0;
        employeePtr->benefit = 0;
        strcpy(employeePtr->status, "FT");
        employeePtr->satisfactionLevel = 0.37;
        employeePtr->numberProject = 2;
        employeePtr->averageMonthlyHours = 158;
        employeePtr->yearsInCompany = 3;
        employeePtr->workAccident = 0;
        employeePtr->promotionsLast5Years = 0;
        */

       top = searchMain(queryPtr);
       employeePtr = &top->data;
       employeePtr->duplicateExists =0;
       char employeeName[EMPLOYEENAME_LEN];
        char jobTitle[JOBTITLE_LEN];
        char status[STATUS_LEN];
        printf("======Server Recived employee Sturct From MainThread======\n");
        printf("%d\n", employeePtr->id);
        strcpy(employeeName, employeePtr->employeeName);
        printf("%s\n",employeeName);
        strcpy(jobTitle, employeePtr->jobTitle);
        printf("%s\n",jobTitle);
        printf("%f\n", employeePtr->overtimePay);
        printf("%f\n", employeePtr->basePay);
        printf("%f\n", employeePtr->benefit);
        strcpy(status, employeePtr->status);
        printf("%s\n",status);
        printf("%f\n", employeePtr->satisfactionLevel);
        printf("%d\n", employeePtr->numberProject); 
        printf("%d\n", employeePtr->averageMonthlyHours);
        printf("%d\n", employeePtr->yearsInCompany);
        printf("%d\n", employeePtr->workAccident);
        printf("%d\n", employeePtr->promotionsLast5Years);
        printf("%d\n", employeePtr->duplicateExists);
        printf("==========================================\n");
    

        send(connectionSocket, employeePtr, sizeof(employeePtr)+STATUS_LEN+JOBTITLE_LEN+EMPLOYEENAME_LEN +sizeof(int)*7+sizeof(double)*3+sizeof(float), 0);
        printf("\nSERVER: Result sent to assistant.\n\n");
    }
    printf("Server shut down at Loop\n");
}