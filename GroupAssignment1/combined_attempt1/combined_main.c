




// Run: gcc combined_main.c -lpthread

#include "header.h"
#include "combined_client.c"
#include "combined_server.c"

int main() {    
    /*
        Automated Input Test
        To modify it, go to manager function in combined_client.c

        // semployeeName, THOMAS SMITH
		// jobTitle, SPECIAL NURSE
		// status, FT

    */
   
    pid_t pid;	//The pid_t data type is a signed integer type which is capable of 					representing a process ID.
	
	/* fork a child process */
	pid = fork();

	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if (pid == 0) { 
        /* client process */
                client();
	}
	else {
         /* Server process */
                server();
	}
	return 0;
}