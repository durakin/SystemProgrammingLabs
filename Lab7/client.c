/*! \file   client.c
 *  \brief  Code of client executable
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "signal.h"
#include "task14.h"
#include "logOutput.h"
#include "timer.h"

#define MIN_PORT 1024
#define MAX_PORT 65635

char g_logPath[INPUT_SIZE] = "log";
int g_idleTime = 10;

/*! \brief Signal handler for server
 */
void ClientTimerHandler(int signum)
{
    if (signum == SIGALRM)
    {
        WriteLogEntry(g_logPath, "Client terminated by timer\n");
        exit(0);
    }
}

void ClientInterruptHandler(int signum)
{
    if (signum == SIGINT)
    {
        WriteLogEntry(g_logPath, "Client terminated by Ctrl+C\n");
        exit(0);
    }
}

void ClientTerminateHandler(int signum)
{
    if (signum == SIGTERM)
    {
        WriteLogEntry(g_logPath, "Client terminated by kill signal\n");
        exit(0);
    }
}

/*! \brief Catches ctrl+C signal, closes socket and terminates server
 *  \details Parses CL arguments, checks them and sends to the server
 */
int main(int argc, char** argv)
{
    if (isatty(STDIN_FILENO) == 0)
    {
        fprintf(stderr, "Streams redirection is prohibited\n");
        exit(EXIT_FAILURE);
    }

    char ip[INPUT_SIZE];
    int portNumber;
    bool helpRequested = false;
    bool ipParsed = false;
    bool portNumberParsed = false;
    bool logPathParsed = false;
    bool idleTimeParsed = false;
    int result;
    while ((result = getopt(argc, argv, "h:a:p:l:t")) != -1)
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
            case 'a':
                strcpy(ip, optarg);
                ipParsed = true;
                break;
        }
    }
    if (helpRequested || argc == 1)
    {
        {
            fprintf(stdout, "Expected arguments:\n-p - Port number\n"
                            "\n-l - Log file path\n"
                            "\n-t - Idle g_idleTime\n"
                            "\n-a - IP-address of server\n");
            exit(EXIT_SUCCESS);
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
    if (!ipParsed)
    {
        fprintf(stderr, "Server address expected\n");
        exit(EXIT_FAILURE);
    }

    struct sigaction saTimer = CreateSAHandler(ClientTimerHandler);
    sigaction(SIGALRM, &saTimer, NULL);
    struct sigaction saInterrupt = CreateSAHandler(ClientInterruptHandler);
    sigaction(SIGINT, &saInterrupt, NULL);
    struct sigaction saTerminate = CreateSAHandler(ClientTerminateHandler);
    sigaction(SIGTERM, &saTerminate, NULL);

    struct itimerval timer = InitTimer(g_idleTime, 0);
    setitimer(ITIMER_REAL, &timer, NULL);

    int8_t radix;
    char number[INPUT_SIZE];

    int socketFileDescriptor;
    struct sockaddr_in name;
    memset((char*) &name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = inet_addr(ip);
    if (INADDR_NONE == name.sin_addr.s_addr)
    {
        perror("inet_addr");
        exit(1);
    }
    name.sin_port = htons((u_short) portNumber);
    socketFileDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketFileDescriptor < 0)
    {
        perror("socket");
        exit(1);
    }

    while (true)
    {
        printf("Enter base of numeral system (2 - 20)\n");
        radix = (int8_t) CheckedInputInt(RadixInputCheck);
        printf("Enter number in chosen system. Use \'A\' - \'J\' as"
               "digits for >10-based systems\n");

        while (true)
        {
            scanf("%s", number);
            if (CheckIntOverflow(number, radix) &&
                CheckRadixMatch(number, radix))
            {
                break;
            }
            printf("Wrong format or too big number!\n");
        }

        RollbackTimer(&timer, g_idleTime, 0);

        taskData* data;
        data = (taskData*) malloc(sizeof(taskData));
        strcpy(data->number, number);
        data->radix = radix;

        int resSend;
        resSend = (int) sendto(socketFileDescriptor, data, sizeof(taskData),
                               0,
                               (struct sockaddr*) &name, sizeof(name));
        if (0 > resSend)
        {
            perror("sendto");
            free(data);
            exit(1);
        }
        WriteLogEntry(g_logPath, "Sent task\n");
        free(data);
    }
    close(socketFileDescriptor);
    return 0;
}

