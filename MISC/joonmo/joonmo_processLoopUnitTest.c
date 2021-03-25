
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 	// for exit(1)
#include <unistd.h>	// for fork
#include <sys/wait.h>
int main()
{
    // this code will eventually get moved into an overall client function
    int pause = 0;
    for (int i = 0; i < 2; i++)
    {
        pid_t pid;
        pid = fork(); // creates a child process
        pause = 0;
        if (pid == 0) // child process
        {
            printf("Child\n");
            exit(0);
        }
        else if (pid > 0) // parent process
        {
            wait(NULL);
            printf("Parent\n");
            
            sleep(2);
            pause=1;
        }
        else
        {
            printf("fork error");
            exit(1);
        }
        while(pause ==0){
            continue;
        }

    }
   
    return 0;
}