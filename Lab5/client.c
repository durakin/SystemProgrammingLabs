#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "socketOperations.h"
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
        fprintf(stderr, "Socket name and port number expected.\n");
        return EXIT_FAILURE;
    }


    int portNumber = atoi(argv[2]);

    struct sockaddr_in name;
    int socketFileDescriptor = 0;
    socketFileDescriptor = ConnectToDgramSocket(argv[1], portNumber, &name);
    if (socketFileDescriptor <= 0)
    {
        perror("socket");
    }

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


        SendToSocket(socketFileDescriptor, name, data, sizeof(taskData));

    } while (!0);
    close(socketFileDescriptor);
    return 0;
}