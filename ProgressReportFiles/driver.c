#include "michael_PR.c"
#include "parker.c"

// void main(){
//     LLTest();
//     printf("\n\n\n");
//     SSThreadsTest();
// }

// parkers client main to integrate
int main()
{
    // this code will eventually get moved into an overall client function

    for (int i = 0; i < 2; i++)
    {
        pid_t pid;
        pid = fork(); // creates a child process

        if (pid == 0) // child process
        {
            manager(); // asking user for input query

            exit(0);
        }
        else if (pid > 0) // parent process
        {
            wait(NULL);
            assistant(); // fetching query results for the Manager process
        }
        else
        {
            printf("fork error");
            exit(1);
        }
    }

    return 0;
}