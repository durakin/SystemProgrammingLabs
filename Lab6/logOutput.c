#include "logOutput.h"
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include "input.h"
#include "timer.h"


/*! \brief Writes info from buffer by pointer into file
 *
 *  \param fd    File descriptor
 *  \param info  Variable with information that will be loaded into file
 *  \param size  The number of bytes that will be loaded into file
 *
 *  \return 0 on success, -1 otherwise
 */
int WriteInfo(int fd, void* info, size_t size)
{
    int writeReturn = (int) write(fd, info, size);
    if (writeReturn == -1)
    {
        perror("Write into file went wrong.");
        return -1;
    }
    if (writeReturn == 0)
    {
        perror("Nothing was written.");
        return -1;
    }
    return 0;
}

int OpenFile(int* fd, char* filename)
{
    *fd = open(filename, O_WRONLY | O_CREAT | O_APPEND);
    if (*fd < 0)
    {
        return -1;
    }
    return 0;
}

void writeLogEntry(char* logPath, char* info)
{
    int fd;
    if (OpenFile(&fd, logPath) != 0)
    {
        perror("log file");
        return;
    }
    char* timeString = GetTimeString();
    WriteInfo(fd, timeString, strlen(timeString));
    WriteInfo(fd, "\n", sizeof(char));
    WriteInfo(fd, info, INPUT_SIZE);
    WriteInfo(fd, "\n", sizeof(char));
    fsync(fd);
    close(fd);
}
