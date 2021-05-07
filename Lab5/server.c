#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "input.h"
#include "task14.h"
#include "socketOperations.h"

typedef struct
{
    char number[INPUT_SIZE];
    int8_t radix;
} taskData;

int server(int serverSocket)
{
    struct sockaddr_in clientName;
    socklen_t clientNameLength = sizeof(clientName);
    taskData* data;
    data = (taskData*) malloc(sizeof(taskData));

    while (!0)
    {
        int recvResult = receiveFromSocket(serverSocket, clientName, data,
                                           sizeof(taskData));
        if (recvResult == -1)
        {
            perror("recvfrom");
        }
        if (recvResult <= 0)
        {
            return 0;
        }
        char reversedNumber[INPUT_SIZE];
        char* number = data->number;
        int8_t radix = data->radix;

        for (int i = (int) strlen(number) - 1; i >= 0; i--)
        {
            reversedNumber[strlen(number) - (i + 1)] = number[i];
        }
        reversedNumber[strlen(number)] = '\0';

        while (reversedNumber[strlen(reversedNumber) - 1] == '0')
        {
            reversedNumber[strlen(reversedNumber) - 1] = '\0';
        }

        printf("Original: %s\n", number);
        printf("To decimal: %d\n", AnyNumeralSystemToDecimal(number, radix));
        printf("Reversed: %s\n", reversedNumber);
        if (CheckIntOverflow(reversedNumber, radix))
        {
            printf("Reversed to decimal: %d\n",
                   AnyNumeralSystemToDecimal(reversedNumber, radix));
        }
        else
        {
            printf("Reversed number is too big");
        }
    }
    return 0;
}

int main(int argc, char* const argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Too few parameters.\n");
        return EXIT_FAILURE;
    }
    int socketFileDescriptor;
    int portNumber = atoi(argv[1]);
    socketFileDescriptor = PrepareServerDgramSocket(portNumber);
    if (socketFileDescriptor == -1)
    {
        return 0;
    }

    do
    {
        server(socketFileDescriptor);
    } while (true);
    close(socketFileDescriptor);
    return 0;
}