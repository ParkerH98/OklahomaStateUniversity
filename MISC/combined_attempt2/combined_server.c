#include "header.h"



void enqueue(struct ListMonitor* index, struct EmployeeStructure* payload){
    int first = 0;
    struct ListEntry* temp;

    if (index->head == NULL){
        first = 1;
    }
    temp = malloc(sizeof(struct ListEntry));

    temp->data = payload;
    temp->next = NULL;
    temp->last = index->tail;
    if (!first){
        index->tail->next = temp;
    }
    index->tail = temp;

    if (first){
        index->head = temp;
    }
};

void disqueue(struct ListMonitor* index, struct ListEntry* target){
    struct ListEntry* temp;
    if (target == index->head){
        printf("Case One");
        fflush(stdout);
        temp = target;
        printf("Temp Assigned.\n");
        fflush(stdout);
        index->head = index->head->next;
        printf("Index Head Moved.\n");
        fflush(stdout);
        //index->head->last = index->head;
        //printf("Nulling the Last on Head.\n");
        fflush(stdout);
        free(temp->data);
        printf("Freed the Data.\n");
        fflush(stdout);
        free(temp);
        printf("Freed the Memory\n");
        fflush(stdout);
    }
    else if (target == index->tail){
        printf("Case Two");
        fflush(stdout);
        temp = target;
        index->tail = index->tail->last;
        index->tail->next = NULL;
        free(temp->data);
        free(temp);

    }
    else {
        printf("Case Three");
        fflush(stdout);
        temp = target;
        temp->next->last=temp->last;
        temp->last->next=temp->next;
        free(temp->data);
        free(temp);
    }
};

// Function Searches the Salary.txt file by the ID passed in on the employeeStructure object.
void* SalarySearch(void *arg){
	struct EmployeeStructure *test = (struct EmployeeStructure *)arg;
	
	FILE *fp;
	char string[100];
	int id;
	float basePay;
	float overtimePay;
    float benefit;

    // Open File.
	fp = fopen("inputTxtFiles//Salary.txt","r");
    // Iterate across the File, checking the ID Value from each line.
	while(fgets(string, 100, fp)){
		sscanf(string,"%d",&id);
        // IF we find the ID we're looking for, read the whole line into the DataStructure directly if possible,
        // and bounce it through a different thing if the compiler screams too loudly.
		if (id == test->id){

			// NOTE: For some reason, the compiler identifies the pointers to the Employee Structure object as
			// being pointers to a double, instead of a float. I've worked around by giving it some local
			// variables to play with. Probably a minor slowdown here, but since we only read full lines once per
			// lookup it shouldn't contribute too much to runtime as the problem scales.

			sscanf(string,"%d\t%[^\t]\t%f\t%f\t%f\t%s",&id,test->jobTitle,&basePay,&overtimePay,&benefit,test->status);
			test->basePay = basePay;
			test->overtimePay = overtimePay;
			test->benefit = benefit;
			break;
		}
	}
	fclose(fp);
	return NULL;
}

// Virtually identical to the Salary Search function above. Searches the Satisfaction file.
void* SatisfactionSearch(void *arg){
	struct EmployeeStructure *test = (struct EmployeeStructure *)arg;
	
	FILE *fp;
	char string[100];
	int id;
	float satisfactionLevel;
    int i = 0;

    // Open up the file.
	fp = fopen("inputTxtFiles//Satisfaction.txt","r");

    // Iterate across the file, checking IDs. When we find the right one, scan in the line.
	while(fgets(string, 100, fp)){
		sscanf(string,"%d",&id);
		if (id == test->id){

            // Yes, I'm using a (frankly hideous) scanf to find these. 
            // We're working with a fixed format so the usual problems with scanf are absent.

			sscanf(string,"%d\t%f\t%d\t%d\t%d\t%d\t%d",&id,&satisfactionLevel,&test->numberProject,&test->averageMonthlyHours,
				&test->yearsInCompany,&test->workAccident,&test->promotionsLast5Years);
			test->satisfactionLevel = satisfactionLevel;

			break;
		}
	}
	fclose(fp);
	return NULL;
}

// ThreadSpawn takes in an Employee Structure Pointer, and then spawns the threads to
// search the Salary and Satisfaction files.
void ThreadSpawn(struct EmployeeStructure *target){

	pthread_t TID_1;
	pthread_t TID_2;

	pthread_create(&TID_1, NULL, SalarySearch, target);
	pthread_create(&TID_2, NULL, SatisfactionSearch, target);
	pthread_join(TID_1, NULL);
	pthread_join(TID_2, NULL);

};

void *mainTheadFunc(void *queryFromClient)
{
    struct Query* pQueryFromClient = queryFromClient;
	struct EmployeeStructure* pEmployeeStruct = malloc(sizeof *pEmployeeStruct); //Introduced by M Oliver.
    struct ListMonitor* index = malloc(sizeof (struct ListMonitor)); //Introduced by M Oliver.
	FILE *fp;
    char buff[255];

    // printf("Comes Here\n");
    fp = fopen("inputTxtFiles/Name.txt", "r");
    while (fgets(buff, sizeof(buff), fp)) {
        char * employeeIDString = strtok(buff, "\t");
        // printf("%s\n", employeeIDString);
		int employeeID = atoi(employeeIDString);
        char * employeeName = strtok(NULL, "");
        // printf("%s\n", employeeName);
        if (employeeName[strlen(employeeName)-1] == '\n'){
            employeeName[strlen(employeeName)-1] = 0;
        }
		if(strcmp(employeeName, pQueryFromClient->employeeName) == 0){

            strcpy(pEmployeeStruct->employeeName, employeeName);
            pEmployeeStruct->id = employeeID;

            // ==================================================================================
            // OLIVER'S CODE
            // ==================================================================================
            
            ThreadSpawn(pEmployeeStruct);
            
            if (strcmp(pEmployeeStruct->status, pQueryFromClient->status) == 0 && 
                strcmp(pEmployeeStruct->jobTitle, pQueryFromClient->jobTitle) == 0){
                enqueue(index, pEmployeeStruct);
            }
            
            // else{
            //     free(pEmployeeStruct);
            // }

            
            // pEmployeeStruct = malloc(sizeof *pEmployeeStruct);

            // ==================================================================================
            // OLIVER'S CODE
            // ==================================================================================

            // printf("%s\n", employeeName);
            // printf("%d\n", employeeID);
        }
    }
    fclose(fp);
    return index;

}



void server()
{

	// return 0;
   
    // ===================Socket Server Setup START===================
    
    
    int server_fd, new_socket, valread, quaryRead;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0}; 
    // char *hello = "Hello from server"; 
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
        printf("Server Listening\n"); 
        struct EmployeeStructure employeeStruct;
        struct EmployeeStructure* pEmployeeStruct = &employeeStruct;
        struct Query query;
        struct Query* pQuery = &query;

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
        printf("Server is Working. Client should wait\n");


        pthread_t mainThread;
        // struct Query queryFromClient;
        void* pTemp;
        // struct EmployeeStructure* pEmployeeStruct;
        struct ListMonitor* index;
        struct ListEntry* readHead;

        // This Testing examples
        // strcpy(queryFromClient.employeeName, "THOMAS SMITH");
        // strcpy(queryFromClient.jobTitle, "SPECIAL NURSE");
        // strcpy(queryFromClient.status, "FT");
        printf("MainThread Recived Query employeeName ========= %s\n",query.employeeName);
        printf("MainThread Recived Query jobTitle ============= %s\n",query.jobTitle);
        printf("MainThread Recived Query status =============== %s\n",query.status);


        if (pthread_create(&mainThread, NULL, mainTheadFunc, (void *)&query) != 0) {	// thread1 create
            printf("Thread1 failed\n");
            // return -1;
        }

        pthread_join(mainThread, &pTemp);	/* Wait until thread1 is finished */
        index = pTemp;

        if (index->tail == NULL){
            printf("Test");
            fflush(stdout);
        }

        readHead = index->head;
        
        while(readHead->next != NULL){
            printf("Loop Iteration is running.\n");
            fflush(stdout);
            pEmployeeStruct = readHead->data;
            printf("Data is Free.\n");
            fflush(stdout);
            // printf("%s\n",pEmployeeStruct->employeeName);
            // printf("%d\n",pEmployeeStruct->id);
            // printf("%s\n",pEmployeeStruct->status);
            // printf("%s\n\n",pEmployeeStruct->jobTitle);
            readHead = readHead->next;
            printf("================HERE====================\n");
            disqueue(index, readHead->last);
        }
        
        pEmployeeStruct = readHead->data;
        // printf("Data is Free.\n");
        // fflush(stdout);
        // printf("%s\n",pEmployeeStruct->employeeName);
        // printf("%d\n",pEmployeeStruct->id);
        // printf("%s\n",pEmployeeStruct->status);
        // printf("%s\n",pEmployeeStruct->jobTitle);
        
        disqueue(index, readHead);
        char employeeName[EMPLOYEENAME_LEN];
        char jobTitle[JOBTITLE_LEN];
        char status[STATUS_LEN];
    
        printf("======Server Recived employee Sturct From MainThread======\n");
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

        send(new_socket , pEmployeeStruct, sizeof(pEmployeeStruct)+ EMPLOYEENAME_LEN + JOBTITLE_LEN + STATUS_LEN +sizeof(int)*7+sizeof(float)*4 , 0 );
        printf("Server sent  empolyee structure\n"); 


    }
        // send(new_socket , hello , strlen(hello) , 0 ); 
        
    
    // ==================Socket Operation END==================
    
    // wait(NULL);
    printf("Server Process is Done!\n");
    // exit(1);    


}