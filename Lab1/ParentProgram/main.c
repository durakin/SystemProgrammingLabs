/*! \file   main.c
 *  \brief  Main file of the child program which contains main function
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>


/*! \brief Spawns a child process
 *
 *  \details Spawn a child process running a new program.
 *
 *  \param program    The name of the program to run.
 *  \param argList    A NULL-terminated list of character strings to be
 *                    passed as the program's argument list.
 *  \return           PID of the spawned process.
 */
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

/*! \brief Main function
 *
 *  \details Main function. Execs Child program by relative path
 *  "../ChildProgram/ChildProgram". If arguments
 *
 *  \return Integer 0 upon successful exit.
 */
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