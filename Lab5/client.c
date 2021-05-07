/*! \file   client.c
 *  \brief  Code of client executable
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "task14.h"


/*! \brief Catches ctrl+C signal, closes socket and terminates server
 *  \details Parses CL arguments, checks them and sends to the server
 */
int main(int argc, const char* argv[])
{
    if (argc != 5)
    {
        fprintf(stderr, "Expected arguments:\nServer address\nPort"
                        "number\nRadix (2-20)\nNumber (use \'A\' - \'J\' as"
                        "digits for >10-based systems\n");
        return EXIT_FAILURE;
    }
    taskData* data;
    data = (taskData*) malloc(sizeof(taskData));

    char* strtolEndptr;
    data->radix = (int8_t) strtol(argv[3], &strtolEndptr, 10);
    if (*strtolEndptr != argv[3][strlen(argv[3])])
    {
        printf("Wrong radix format!\n");
        return 0;
    }
    if (!RadixInputCheck(data->radix))
    {
        printf("Wrong radix format!\n");
        return 0;
    }
    strcpy(data->number, argv[4]);
    if (!(CheckIntOverflow(data->number, data->radix) &&
          CheckRadixMatch(data->number, data->radix)))
    {
        printf("Wrong number format!\n");
        return 0;
    }


    int socketFileDescriptor;
    int portNumber = atoi(argv[2]);
    struct sockaddr_in name;
    memset((char*) &name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = inet_addr(argv[1]);
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

    int resSend;
    resSend = (int) sendto(socketFileDescriptor, data, sizeof(taskData), 0,
                           (struct sockaddr*) &name, sizeof(name));
    if (0 > resSend)
    {
        perror("sendto");
        exit(1);
    }
    close(socketFileDescriptor);
    free(data);
    return 0;
}

