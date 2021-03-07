#include "header.h"
// #include "stdlib.h"

int main(){

    system("gnome-terminal --  bash -c \"tty; exec bash\""); // opens a new terminal
    int file = open("/dev/pts/1", O_WRONLY); // sets the gnome-terminal as a file to write to
    int stdoutDescriptor = dup(1); // copies the file descriptor for stdout
    dup2(file, 1); // writes the stdout file descriptor to that of the new gnome-terminal

    printf("Should display in a new window\n"); // tests that stdout prints to new terminal

    dup2(stdoutDescriptor, 1); // sets the stdout file descriptor back thereby undoing the change

    printf("Should display in vscode\n"); // tests the stdout prints back in original location

    return 0;
}