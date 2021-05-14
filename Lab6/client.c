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

char g_logPath[INPUT_SIZE] = "log";
int g_idleTime = 10;

void ClientSignalHandler(int signum)
{
    if (signum == SIGINT)
    {
        writeLogEntry(g_logPath,"Client terminated by Ctrl+C\n");
        exit(0);
    }
    else if (signum == SIGALRM)
    {
        writeLogEntry(g_logPath, "Client terminated by timer\n");
        exit(0);
    }
    else if (signum == SIGTERM)
    {
        writeLogEntry(g_logPath,"Client terminated by kill signal\n");
        exit(0);
    }
}


/*! \brief Catches ctrl+C signal, closes socket and terminates server
 *  \details Parses CL arguments, checks them and sends to the server
 */
int main(int argc, const char* argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "Expected arguments:\nServer address\nPort"
                        "number\nLog file name\nIdle timeout\n");
        return EXIT_FAILURE;
    }
    strcpy(g_logPath, argv[3]);
    g_idleTime = atoi(argv[4]);

    struct sigaction sa = CreateSAHandler(ClientSignalHandler);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGALRM, &sa, NULL);

    struct itimerval timer = InitTimer(g_idleTime, 0);
    setitimer(ITIMER_REAL, &timer, NULL);


    int8_t radix;
    char number[INPUT_SIZE];
    printf("Enter base of numeral system (2 - 20)\n");
    radix = (int8_t) CheckedInputInt(RadixInputCheck);
    printf("Enter number in chosen system. Use \'A\' - \'J\' as"
           "digits for >10-based systems\n");
    while (true)
    {
        scanf("%s", number);
        if (CheckIntOverflow(number, radix) && CheckRadixMatch(number, radix))
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

    int socketFileDescriptor;
    int portNumber = atoi(argv[2]);
    struct sockaddr_in name;
    memset((char*) &name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = inet_addr(argv[1]);
    if (INADDR_NONE == name.sin_addr.s_addr)
    {
        perror("inet_addr");
        free(data);
        exit(1);
    }
    name.sin_port = htons((u_short) portNumber);
    socketFileDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketFileDescriptor < 0)
    {
        perror("socket");
        free(data);
        exit(1);
    }

    int resSend;
    resSend = (int) sendto(socketFileDescriptor, data, sizeof(taskData), 0,
                           (struct sockaddr*) &name, sizeof(name));
    if (0 > resSend)
    {
        perror("sendto");
        free(data);
        exit(1);
    }
    close(socketFileDescriptor);
    free(data);
    return 0;
}

