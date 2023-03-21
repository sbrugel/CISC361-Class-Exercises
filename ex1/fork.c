#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
/*
Use fork() to create child/grandchild processes

Should print:
    I am the grandchild (#), where ‘#’ is the pid of the grandchild process
    I am the child (#), where ‘#’ is the pid of the child process
    I am the parent (#), where ‘#’ is the pid of the parent process
*/
int main()
{
    int status;
    int pid = fork();

    // Write C code here
    if (pid == 0)
    { // child
        int pid1 = fork();
        if (pid1 == 0)
        {
            int pid2 = getpid();
            printf("I am the grandchild %d\n", pid2);
        }
        else
        {
            int pid2 = getpid();
            printf("I am the child %d\n", pid2);
        }
    }
    else
    {
        int pid1 = getpid();
        printf("I am the parent %d\n", pid1);
    }
    return 0;
}
