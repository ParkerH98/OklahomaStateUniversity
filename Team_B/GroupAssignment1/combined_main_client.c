



// Run Server First
// Run: gcc combined_main_client.c -lpthread -o client

#include "header.h"
#include "combined_client.c"
// #include "combined_server.c"

int main() {
    iterationCount = 1;    
    /*
        Automated Input Test
        To modify it, go to manager function in combined_client.c

        // semployeeName, THOMAS SMITH
		// jobTitle, SPECIAL NURSE
		// status, FT

    */

    client();

	return 0;
}