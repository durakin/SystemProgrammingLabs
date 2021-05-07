#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "socketOperations.h"
#include "input.h"
#include "task14.h"

#define MAX_PORT_NUMBER 65365
#define MIN_PORT_NUMBER 1024

typedef struct
{
    char number[INPUT_SIZE];
    int8_t radix;
} taskData;


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

    int portNumber = atoi(argv[2]);
    int socketFileDescriptor;
    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = inet_addr(argv[1]);

    if ((portNumber > MAX_PORT_NUMBER) || (portNumber < MIN_PORT_NUMBER))
    {
        perror("bad_port");
        exit(1);
    }
    memset((char*) &name, 0, sizeof(name));
    if (name.sin_addr.s_addr == INADDR_NONE)
    {
        perror("bad_inet_addr");
        exit(1);
    }
    name.sin_port = htons((u_short) portNumber);
    socketFileDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketFileDescriptor < 0)
    {
        perror("bad_socket");
        exit(1);
    }

    char* strtolEndptr;
    data->radix = (int8_t) strtol(argv[3], &strtolEndptr, 10);

    if (*strtolEndptr != argv[3][strlen(argv[3])])
    {
        printf("Wrong radix!\n");
        return 0;
    }
    if (!RadixInputCheck(data->radix))
    {
        printf("Wrong radix!\n");
    }
    strcpy(data->number, argv[4]);
    if(!(CheckIntOverflow(data->number, data->radix) &&
     CheckRadixMatch(data->number, data->radix)))
    {
        printf("Wrong number!\n");
    }
    SendToSocket(socketFileDescriptor, name, data, sizeof(taskData));
    close(socketFileDescriptor);
    return 0;
}
