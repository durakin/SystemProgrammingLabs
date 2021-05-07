//
// Created by Albert Nepomnyashiy on 5/7/2021.
//

#ifndef SOCKETOPERATIONS_H
#define SOCKETOPERATIONS_H


int PrepareServerDgramSocket(int portNumber, struct sockaddr_in* name);

int ConnectToDgramSocket(char* inetAddress, int portNumber,
                         struct sockaddr_in* name);

void SendToSocket(int socketFileDescriptor, struct sockaddr_in name,
                  void* dataBuf, size_t size);

int receiveFromSocket(int socketFileDescriptor, struct sockaddr_in name,
                      void* dataBuf, size_t size);


#endif //SOCKETOPERATIONS_H
