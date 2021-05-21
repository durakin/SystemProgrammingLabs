/*! \file   server.c
 *  \brief  Code of server executable and server's task
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include "task14.h"
#include "logOutput.h"
#include "timer.h"
#include "serverFunctions.h"


char g_logPath[INPUT_SIZE];
int g_idleTime = 10;

/*! \brief SIGALRM signal handler for server
 */
void ServerTimerHandler(int signum)
{
    if (signum == SIGALRM)
    {
        if (access(PATH_TO_CHECK_FILE, F_OK) == 0)
        {
            remove(PATH_TO_CHECK_FILE);
        }
        WriteLogEntry(g_logPath, "Server terminated by timer\n");
        exit(0);
    }
}

/*! \brief SIGINT signal handler for server
 */
void ServerInterruptHandler(int signum)
{
    if (signum == SIGINT)
    {
        if (access(PATH_TO_CHECK_FILE, F_OK) == 0)
        {
            remove(PATH_TO_CHECK_FILE);
        }
        WriteLogEntry(g_logPath, "Server terminated by Ctrl+C\n");
        exit(0);
    }
}

/*! \brief SIGTERM signal handler for server
 */
void ServerTerminateHandler(int signum)
{
    if (signum == SIGTERM)
    {
        if (access(PATH_TO_CHECK_FILE, F_OK) == 0)
        {
            remove(PATH_TO_CHECK_FILE);
        }
        WriteLogEntry(g_logPath, "Server terminated by kill signal\n");
        exit(0);
    }
}

/*! \brief Reads data from socket and calls PerformTask()
 *
 *  \param serverSocket descriptor of socket to listen
 */
int ServerTask(int serverSocket)
{
    struct sockaddr_in clientName;
    socklen_t clientNameLength = sizeof(clientName);
    taskData* data;
    data = (taskData*) malloc(sizeof(taskData));

    struct sigaction saTimer = CreateSAHandler(ServerTimerHandler);
    sigaction(SIGALRM, &saTimer, NULL);
    struct sigaction saInterrupt = CreateSAHandler(ServerInterruptHandler);
    sigaction(SIGINT, &saInterrupt, NULL);
    struct sigaction saTerminate = CreateSAHandler(ServerTerminateHandler);
    sigaction(SIGTERM, &saTerminate, NULL);

    struct itimerval timer = InitTimer(g_idleTime, 0);
    setitimer(ITIMER_REAL, &timer, NULL);


    while (true)
    {
        int recvResult = (int) recvfrom(serverSocket, data, sizeof(taskData),
                                        0,
                                        (struct sockaddr*) &clientName,
                                        &clientNameLength);
        if (-1 == recvResult)
        {
            perror("recvfrom");
        }
        if (recvResult > 0)
        {
            WriteLogEntry(g_logPath, "Got new task\n");
            PerformTask(data);
            RollbackTimer(&timer, g_idleTime, 0);
        }
    }
    if (access(PATH_TO_CHECK_FILE, F_OK) == 0)
    {
        remove(PATH_TO_CHECK_FILE);
    }
    free(data);
    return 0;
}

/*! \brief main function of server
 */
int main(int argc, char** argv)
{
    if (!isatty(STDIN_FILENO))
    {
        fprintf(stderr, "Streams redirection is prohibited\n");
        exit(EXIT_FAILURE);
    }
    if (!isatty(STDOUT_FILENO))
    {
        fprintf(stderr, "Streams redirection is prohibited\n");
        exit(EXIT_FAILURE);
    }

    int portNumber;
    bool helpRequested = false;
    bool portNumberParsed = false;
    bool logPathParsed = false;
    bool idleTimeParsed = false;
    bool checkDisks = false;
    int result;
    while ((result = getopt(argc, argv, "hp:l:t:c")) != -1)
    {
        switch (result)
        {
            case 'h':
                helpRequested = true;
                break;

            case 'p':
                portNumber = atoi(optarg);
                if (MIN_PORT <= portNumber && portNumber <= MAX_PORT)
                {
                    portNumberParsed = true;
                }
                break;
            case 'l':
                strcpy(g_logPath, optarg);
                logPathParsed = true;
                break;
            case 't':
                g_idleTime = atoi(optarg);
                if (g_idleTime > 0)
                {
                    idleTimeParsed = true;
                }
                break;
            case 'c':
                checkDisks = true;
                break;
        }
    }
    if (helpRequested || argc == 1)
    {
        {
            fprintf(stdout, "Expected arguments:\n-p - Port number\n"
                            "\n-l - Log file path\n"
                            "\n-t - Idle time\n"
                            "\n-c - Check file system occupancy\n");
            return EXIT_SUCCESS;
        }
    }
    if (!portNumberParsed)
    {
        fprintf(stderr, "Valid port number expected\n");
        exit(EXIT_FAILURE);
    }
    if (!logPathParsed)
    {
        fprintf(stderr, "Log file name expected\n");
        exit(EXIT_FAILURE);
    }
    if (!idleTimeParsed)
    {
        fprintf(stderr, "Valid idle time expected\n");
        exit(EXIT_FAILURE);
    }

    if (checkDisks)
    {
        fprintf(stdout, "Free space on FS: %lu blocks\n",
                FsFreeSize(g_logPath));
    }

    ServerCheckRunning(portNumber);

    int socketFileDescriptor;
    struct sockaddr_in name;
    socketFileDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int i = 1;
    setsockopt(socketFileDescriptor, SOL_SOCKET, SO_REUSEADDR,
               (const char*) &i, sizeof(i)
    );
    bzero((char*) &name, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons((u_short) portNumber);
    name.sin_addr.s_addr = INADDR_ANY;
    if (-1 == bind(socketFileDescriptor, (const struct sockaddr*) &name,
                   sizeof(name)))
    {
        perror("bind ");
        close(socketFileDescriptor);
        exit(1);
    }
    ServerTask(socketFileDescriptor);
    close(socketFileDescriptor);
}
