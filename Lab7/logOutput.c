/*! \file   logOutput.c
 *  \brief  Implements functions declared in logOutput.h and defines
 *  essential functions for it.
 */

#include "logOutput.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "input.h"
#include "timer.h"
#include <sys/vfs.h>


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

/*! \brief Opens file
 *
 *  \details Opens file, changes file descriptor by pointer and
 *  reports errors.
 *
 *  \param fd        File descriptor pointer
 *  \param filename  Name of file to open
 *
 *  \return 0 on success, -1 otherwise
 */
int OpenFile(int* fd, char* filename)
{
    *fd = open(filename, O_WRONLY | O_CREAT | O_APPEND);
    write(*fd, "", 0);
    if (*fd < 0)
    {
        return -1;
    }
    return 0;
}

unsigned long fsFreeSize(char* vfsPath)
{
    struct statfs buf;
    statfs(vfsPath, &buf);
    return buf.f_bfree;
}

void WriteLogEntry(char* logPath, char* info)
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
    close(fd);
}
