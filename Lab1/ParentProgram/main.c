#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int spawn(char* program, char** argList)
{
    pid_t childPid;
    childPid = fork();
    if (childPid == 0)
    {
        execl(program, NULL, NULL);
        fprintf(stderr, "an error occurred in exec\n");
        abort();
    }
    else
    {
        printf("This is a parent process");
    }
    return 0;
}

int main()
{
    int childStatus;
    char* child = "../ChildProgram/ChildProgram";
    char* argList[] = {NULL};
    spawn(child, argList);
    wait(&childStatus);
    if (WIFEXITED(childStatus))
    {
        printf("The child process exited normally with code %d.\n",
               WEXITSTATUS(childStatus)
        );
    }
    else
    {
        printf("The child process exited abnormally.\n");
    }
    return 0;
}