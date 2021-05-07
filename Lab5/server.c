#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int server(int serverSocket)
{
    struct sockaddr_in clientName;
    socklen_t clientNameLength = sizeof(clientName);
    while (!0)
    {
        int length = 0;
        char* text = NULL;
        int recvResult = (int) recvfrom(serverSocket, &length, sizeof(length),
                                        0,
                                        (struct sockaddr*) &clientName,
                                        &clientNameLength
        );
        if (-1 == recvResult)
        {
            perror("recvfrom");
        }
        if (0 >= recvResult)
        {
            return 0;
        }
        text = (char*) malloc(length);
        bzero(text, length);
        recvResult = recvfrom(serverSocket, text, length, 0,
                              (struct sockaddr*) &clientName,
                              &clientNameLength
        );
        printf("%s\n", text);
        if (0 == strcmp(text, "adios amigo"))
        {
            free(text);
            break;
        }
        free(text);
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