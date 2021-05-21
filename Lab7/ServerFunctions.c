/*! \file   ServerFunctions.c
 *  \brief  Implements function from ServerFunction.h
 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "ServerFunctions.h"


void ServerCheckRunning(int port)
{
    if (access(PATH_TO_CHECK_FILE, F_OK) == 0)
    {
        fprintf(stderr, "Server is already running\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        int fd = open(PATH_TO_CHECK_FILE, O_WRONLY | O_CREAT| O_APPEND, 0660);
        if (fd == -1)
        {
            fprintf(stderr, "Couldn't open or create essential temp file\n");
            exit(EXIT_FAILURE);
        }
        char portStr[PORT_LENGTH];
        sprintf(portStr, "%d", port);
        int writtenBytes = (int) write(fd, portStr, PORT_LENGTH);
        if (writtenBytes <= 0)
        {
            fprintf(stderr, "Couldn't write to essential temp file\n");
            exit(EXIT_FAILURE);
        }
    }
}
