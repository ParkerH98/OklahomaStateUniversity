#include "header.h"
#include "parker.c"

int main(int argc, char *argv[])
{
    iterationCount = 1; // initializes the iterationCount later used to check if a new terminal should be opened -- see printToTerminal()
    if (argc == 1) // an IP address wasn't entered
    {
        printf("Please enter a server IP address to run the program\n");
        exit(1);
    }
    printf("Assistant: Entered IP of Server %s\n\n", argv[1]); // gets inputted IP of server
    strcpy(IP, argv[1]);
    
    runClient(); // runs the entire client program
    return 0;
}