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

char g_logPath[INPUT_SIZE] = "log";
int g_idleTime = 10;

void ServerSignalHandler(int signum)
{
    if (signum == SIGINT)
    {
        WriteLogEntry(g_logPath, "Server terminated by Ctrl+C\n");
        exit(0);
    }
    else if (signum == SIGALRM)
    {
        WriteLogEntry(g_logPath, "Server terminated by timer\n");
        exit(0);
    }
    else if (signum == SIGTERM)
    {
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

    struct sigaction sa = CreateSAHandler(ServerSignalHandler);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGALRM, &sa, NULL);

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
    free(data);
    return 0;
}



/*! \brief main function of server
 */
int main(int argc, char* const argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Expected arguments:\nPort number\n"
                        "Log file name\nIdle timeout\n");
        return EXIT_FAILURE;
    }
    int socketFileDescriptor = -1;
    int portNumber = atoi(argv[1]);
    strcpy(g_logPath, argv[2]);
    g_idleTime = atoi(argv[3]);
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