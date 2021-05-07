#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


int PrepareServerDgramSocket(int portNumber, struct sockaddr_in* name)
{
    int socketFileDescriptor;
    socketFileDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int i = 1;
    setsockopt(socketFileDescriptor, SOL_SOCKET, SO_REUSEADDR,
               (const char*) &i, sizeof(i)
    );
    bzero((char*) name, sizeof(*name));
    name->sin_family = AF_INET;
    name->sin_port = htons((u_short) portNumber);
    name->sin_addr.s_addr = INADDR_ANY;
    if (bind(socketFileDescriptor, (const struct sockaddr*) name,
             sizeof(*name) )== -1)
    {
        perror("bind");
        close(socketFileDescriptor);
        return -1;
    }
    return socketFileDescriptor;
}

int ConnectToDgramSocket(const char* inetAddress, int portNumber,
                         struct sockaddr_in* name)
{
    memset((char*) name, 0, sizeof(*name));
    name->sin_family = AF_INET;
    name->sin_addr.s_addr = inet_addr(inetAddress);
    if (INADDR_NONE == name->sin_addr.s_addr)
    {
        perror("inet_addr");
        exit(1);
    }
    name->sin_port = htons((u_short) portNumber);
    int socketFileDescriptor;
    socketFileDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketFileDescriptor < 0)
    {
        perror("socket");
        return -1;
    }
    return socketFileDescriptor;
}

void SendToSocket(int socketFileDescriptor, struct sockaddr_in name,
                  void* dataBuf, size_t size)
{
    int sendResult;
    sendResult = (int) sendto(socketFileDescriptor, dataBuf, size, 0,
                              (struct sockaddr*) &name, sizeof(name));

    if (sendResult <= 0)
    {
        perror("sendto");
        printf("Error sending\n");
    }
}

int receiveFromSocket(int socketFileDescriptor, struct sockaddr_in name,
                      void* dataBuf, size_t size)
{
    socklen_t nameLength = sizeof (name);
    int recvResult = (int) recvfrom(socketFileDescriptor, dataBuf, size,
                              0, (struct sockaddr *) &name, &nameLength);
    if (recvResult <= 0)
    {
        perror("recvfrom");
        return -1;
    }
    printf("Read");
    return 0;
}