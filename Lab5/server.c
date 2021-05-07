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

int server(int serverSocket)
{
    struct sockaddr_in clientName;
    socklen_t clientNameLength = sizeof(clientName);
    taskData* data;
    data = (taskData*) malloc(sizeof(taskData));

    while (!0)
    {
        char* text = NULL;
        int recvResult = (int) recvfrom(serverSocket, data, sizeof(taskData),
                                        0,
                                        (struct sockaddr*) &clientName,
                                        &clientNameLength);
        if (-1 == recvResult)
        {
            perror("recvfrom");
        }
        if (0 >= recvResult)
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
    int socketFileDescriptor = -1;
    int portNumber = atoi(argv[1]);
    struct sockaddr_in name;
    int clientSentQuitMessage;
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
    do
    {
        clientSentQuitMessage = server(socketFileDescriptor);
    } while (!clientSentQuitMessage);
    close(socketFileDescriptor);
    return 0;
}