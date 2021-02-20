#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>

void printProcess(int, char, int *);
void helper(int);

struct message_buffer{
    long msg_type;
    char text;
};

int main()
{
//    int *n = mmap(NULL, 10 * sizeof(int), 
//                             PROT_READ | PROT_WRITE, 
//                             MAP_SHARED | MAP_ANONYMOUS, 
//                             0, 0);
   
   
    int i = 0;
    char letter = 'A';


    int msgid;
    if((msgid = msgget(IPC_PRIVATE, 0600 | IPC_CREAT)) == -1)
    {
        printf("Error making msgid!");
        exit(1);
    }

    // pid_t pid = fork();

    // if(pid == 0)
    // {
    //     helper(msgid);
    // }
    
    struct message_buffer message;
    message.msg_type = 1;
    message.text = 'A';

    printf("MsgID: %d\nMsg Type: %d\n", msgid, (int)message.msg_type);

    if(msgsnd(msgid, &message, sizeof(message), 0) == -1)
    {
        perror("msgsnd");
        exit(1);
    }
    printf("Message sent!");

    while(wait(NULL) != -1 || errno != ECHILD){;}

    return 0;
}

// void printProcess(int key, char letter, int *n)
// {
//     struct messageBuffer message;
    
//     printf("Child: %d\n", (int)letter);
//     message.type = (int)letter;
//     message.text[0] = letter;

//     int msgid;
//     if((msgid = msgget(key, 0666 | IPC_CREAT)) == -1)
//     {
//         printf("Error making msgid!");
//         exit(1);
//     }
    
//     if((msgsnd(msgid, &message, sizeof(char) * 12, 0)) == -1)
//     {
//         perror("msgsnd");
//         exit(1);
//     }

//     exit(1);
// }

void helper(int msgid)
{
    printf("Im the helper!\n");
    
    struct message_buffer recieve;

    if((msgrcv(msgid, &recieve, sizeof(recieve), 1, 0)) == -1)
    {
        perror("msgrcv");
        exit(1);
    }


    if(msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
    }
    exit(1);
}