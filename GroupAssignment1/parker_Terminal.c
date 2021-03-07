#include "header.h"
#include "stdlib.h"

int main(){

    system("gnome-terminal --  bash -c \"tty; exec bash\"");
    int file = open("/dev/pts/1", O_WRONLY);
    int stdoutt = dup(1); // file descriptor for stdout
    dup2(file, 1);

    printf("TEST\n");

    dup2(stdoutt, 1);

    return 0;
}