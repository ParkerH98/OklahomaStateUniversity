#include "michael_PR.c"
#include "parker.c"
#include "joonmo_PR.c"



// gcc driver.c -lpthread

int main()
{
    printf("MICHAEL OLIVER TEST BEGINS HERE\n");
    LLTest();
    printf("\n\n");
    SSThreadsTest();
    printf("\nMICHAEL OLIVER TEST ENDS HERE\n");

    
    printf("JOONMO KOO TEST BEGINS HERE\n");
    serverMainThreadUnitTest();
    socketUnitTest();
    toLowerUnitTest();
    printf("\nJOONMO KOO TEST ENDS HERE\n");



    printf("PARKER HAGUE TEST BEGINS HERE\n");

    pid_t pid;
    pid = fork(); // creates a child process

    if (pid == 0) // child process
    {
        serverSocket_SendReceive(); // starts server and begins listening

        exit(0);
    }
    else if (pid > 0) // parent process
    {
        runClient(); // runs manager and assistant functions
    }
    printf("PARKER HAGUE TEST ENDS HERE\n");

    return 0;
}