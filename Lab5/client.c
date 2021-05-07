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
    if (argc != 3)
    {
        fprintf(stderr, "Socket name and port number expected.\n");
        return EXIT_FAILURE;
    }

    taskData* data;
    data = (taskData*) malloc(sizeof (taskData));

    int portNumber = atoi(argv[2]);
    int socketFileDescriptor;
    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = inet_addr(argv[1]);
    if (INADDR_NONE == name.sin_addr.s_addr)
    {
        printf("Wrong address!\n");
        exit(1);
    }
    if ((portNumber > MAX_PORT_NUMBER) || (portNumber < MIN_PORT_NUMBER))
    {
        printf("Wrong port!\n");
        exit(1);
    }
    memset((char *) &name, 0, sizeof (name));
    if (INADDR_NONE == name.sin_addr.s_addr)
    {
        perror("inet_addr");
        exit(1);
    }
    name.sin_port = htons((u_short)portNumber);
    socketFileDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (0 > socketFileDescriptor)
    {
        perror("socket");
    }

    do
    {

        printf("Enter base of numeral system (2 - 20)\n");
        data->radix = (int8_t) CheckedInputInt(RadixInputCheck);
        printf("Enter number in chosen system. Use \'A\' - \'J\' as"
               "digits for >10-based systems\n");
        while (true)
        {
            scanf("%s", data->number);
            if (CheckIntOverflow(data->number, data->radix) &&
                CheckRadixMatch(data->number, data->radix))
            {
                break;
            }
            printf("Wrong format or too big number!\n");
        }


        SendToSocket(socketFileDescriptor, name, data, sizeof(taskData));

    } while (!0);
    close(socketFileDescriptor);
    return 0;
}