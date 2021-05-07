#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

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
    do
    {
        message[0] = '\0';
        printf("Please, enter a string to send to server.\n");
        printf("To quit enter \"adios amigo\"\n");
        fgets(message, 256, stdin);
        message[strlen(message) - 1] = 0;
        int resSend = 0;
        int length = strlen(message) + 1;
        resSend = sendto(socketFileDescriptor, &length, sizeof(length), 0,
                         (struct sockaddr*) &name, sizeof(name)
        );
        if (0 > resSend)
        {
            perror("sendto");
        }
        resSend = sendto(socketFileDescriptor, message, length, 0,
                         (struct sockaddr*) &name, sizeof(name)
        );
        if (0 > resSend)
        {
            perror("sendto");
        }
        if (0 == strcmp(message, "adios amigo"))
        {
            break;
        }
    } while (!0);
    close(socketFileDescriptor);
    return 0;
}