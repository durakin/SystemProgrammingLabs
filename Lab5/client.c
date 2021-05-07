#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "input.h"
#include "task14.h"

typedef struct
{
    char number[INPUT_SIZE];
    int8_t radix;
} taskData;


int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Socketname and port number expected.\n");
        return EXIT_FAILURE;
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
    if (0 > socketFileDescriptor)
    {
        perror("socket");
    }
    char message[256];
    taskData* data;
    data = (taskData*) malloc(sizeof(taskData));

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

        int resSend = 0;
        int length = strlen(message) + 1;
        resSend = sendto(socketFileDescriptor, data, sizeof(taskData), 0,
                         (struct sockaddr*) &name, sizeof(name)
        );
        if (0 > resSend)
        {
            perror("sendto");
        }
    } while (!0);
    close(socketFileDescriptor);
    return 0;
}