#include "joonmo.c"

// Run: gcc driver_server.c -lpthread -o server

int main(int argc, char *argv[])
{
    // if (argc == 1)
    // {
    //     printf("Please enter a server IP address to run the program\n");
    //     exit(1);
    // }
    // printf("Assistant: Entered IP of Server %s\n\n", argv[1]);
    // strcpy(IP, argv[1]);

    runServer();
    return 0;
}