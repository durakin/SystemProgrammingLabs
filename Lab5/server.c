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


/*! \brief Catches ctrl+C signal, closes socket and terminates server
 *
 *  \param signum caught signal
 *  \param socketToClose descriptor of socket to close before terminating
 */
void serverKiller(int signum, int socketToClose) {
    printf("Caught signal %d\n", signum);
    if(signum == SIGINT)
    {
        printf("Terminating server\n");
        close(socketToClose);
        exit(signum);
    }
}

/*! \brief Reads data from socket and calls PerformTask()
 *
 *  \param serverSocket descriptor of socket to listen
 */
int serverTask(int serverSocket)
{
    struct sockaddr_in clientName;
    socklen_t clientNameLength = sizeof(clientName);
    taskData* data;
    data = (taskData*) malloc(sizeof(taskData));
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
        PerformTask(data);
    }
    free(data);
    return 0;
}

/*! \brief main function of server
 */
int main(int argc, char* const argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Too few parameters.\n");
        return EXIT_FAILURE;
    }
    int socketFileDescriptor = -1;
    int portNumber = atoi(argv[1]);
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
    signal(SIGINT, (void*) serverKiller);
    do
    {
        serverTask(socketFileDescriptor);
    } while (true);
}