/*! \file   FileIO.c
 *  \brief  Implements functions declared in FileIO.c and defines other
 *  functions essential for this.
 */

#include <stdbool.h>
#include "FileIO.h"
#include <inttypes.h>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Input.h"


#define TEMP_FILE_NAME "_temp"

/*! \brief Checks whether the file from the path exists or not
 *
 *  \param path Path to the file
 *
 *  \return true if exists, false otherwise
 */
bool FileExistCheck(char* path)
{
    return (access(path, F_OK) == 0);
}

/*! \brief Returns size of file
 *
 *  \param fd File descriptor
 *
 *  \return Size of file
 */
int GetFileSize(int fd)
{
    struct stat info;
    int fstatSuccess = fstat(fd, &info);
    if (fstatSuccess)
    {
        perror("Getting file info went wrong.");
    }
    return (int) info.st_size;
}

/*! \brief Deletes file from working directory by name
 *
 *  \param filename Name of file
 *
 *  \return 0 on success, -1 otherwise
 */
int DeleteFile(char* filename)
{
    int removeReturn = remove(filename);
    if (removeReturn != 0)
    {
        perror("File delete error");
        return -1;
    }
    return 0;
}

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

/*! \brief Writes meta information (maximal size of island groups' name)
 *  into beginning of the file (if the file is empty)
 *
 *  \param fd         File descriptor
 *  \param inputSize  Meta information (maximal size of island groups' name)
 *
 *  \return 0 on success, -1 otherwise
 */
int WriteMeta(int fd, int32_t inputSize)
{
    lseek(fd, 0, SEEK_SET);
    if (GetFileSize(fd) == 0)
    {
        return WriteInfo(fd, &inputSize, sizeof(int32_t));
    }
    return -1;
}

/*! \brief Reads information from the file
 *
 *  \param fd    File descriptor
 *  \param info  Variable with information that will be loaded into file
 *  \param size  The number of bytes that will be loaded into file
 *
 *  \return 0 on success, -1 otherwise
 */
int ReadInfo(int fd, void* info, size_t size)
{
    int readReturn = (int) read(fd, info, size);

    if (readReturn == -1)
    {
        perror("Read error");
        return -1;
    }

    if (readReturn == 0)
    {
        perror("Nothing has been read.");
        return -1;
    }

    return readReturn;
}

/*! \brief Reads meta information (size of one group) from the file
 *
 *  \param fd File descriptor
 *
 *  \return 0 on success, -1 otherwise
 */
int ReadMeta(int fd, int* inputSize)
{
    lseek(fd, 0, SEEK_SET);
    int readReturn;
    readReturn = ReadInfo(fd, (void*) inputSize, sizeof(int32_t));
    if (readReturn <= 0)
    {
        perror("Meta info error");
        return -1;
    }
    return 0;
}

/*! \brief Moves the pointer in the file to group by name
 *
 *  \param fd         File descriptor
 *  \param groupName  Name of the group to seek
 *  \param inputSize  Maximal size of island groups' name
 *
 *  \return 0 if group was found and seek set, -1 otherwise
 */
int SeekToGroupByName(int fd, char* groupName, int inputSize)
{
    lseek(fd, sizeof(int32_t), SEEK_SET);
    char currentGroupName[MAX_INPUT_SIZE];
    strcpy(currentGroupName, groupName);

    while (lseek(fd, 0, SEEK_CUR) < GetFileSize(fd))
    {
        ReadInfo(fd, &currentGroupName, sizeof(char) *
                                        inputSize);
        if (strcmp(groupName, currentGroupName) == 0)
        {
            lseek(fd, (int) -sizeof(char) * inputSize, SEEK_CUR);
            return 0;
        }
        lseek(fd, sizeof(int32_t) * 2, SEEK_CUR);
    }

    return -1;
}


/*! \brief Writes information about island group to the file.
 *
 *  \details This function doesn't check if name is unique and information is
 *  consistent. Should only be used as in AddIslandGroup().
 *  be called after additional
 *
 *  \param fd                     File descriptor
 *  \param islandGroupName        Name of island group
 *  \param islandGroupIslands     Overall number of islands in group
 *  \param islandGroupInhIslands  Number of inhabitant islands in group
 *  \param inputSize              Maximal size of island groups' name
 */
void WriteIslandGroup(int fd, char* islandGroupName,
                      int32_t islandGroupIslands,
                      int32_t islandGroupInhIslands,
                      int inputSize)
{
    lseek(fd, 0, SEEK_END);
    WriteInfo(fd, islandGroupName, sizeof(char) * inputSize);
    WriteInfo(fd, (void*) &islandGroupIslands, sizeof(int32_t));
    WriteInfo(fd, (void*) &islandGroupInhIslands, sizeof(int32_t));
}


int AddIslandGroup(int fd, char* islandGroupName, int32_t islandGroupIslands,
                   int32_t islandGroupInhabitantIslands, int inputSize)
{
    if (islandGroupInhabitantIslands > islandGroupIslands ||
        SeekToGroupByName(fd, islandGroupName, inputSize) != -1)
    {
        return -1;
    }
    WriteIslandGroup(fd, islandGroupName, islandGroupIslands,
                     islandGroupInhabitantIslands, inputSize);
    return 0;
}

bool DeleteGroupByName(int* fd, char* islandGroupName, char* filename,
                       int inputSize)
{
    int tempFd;
    if (PrepareNewFile(&tempFd, TEMP_FILE_NAME, inputSize) != 0)
    {
        printf("Something went wrong while creating temp file\n");
        return false;
    }
    char stringInputBuffer[MAX_INPUT_SIZE];
    int32_t currentIslandGroupIslands;
    int32_t currentIslandGroupInhabitantIslands;
    lseek(*fd, sizeof(int32_t), SEEK_SET);
    bool found = false;
    while (lseek(*fd, 0, SEEK_CUR) < GetFileSize(*fd))
    {
        ReadInfo(*fd, stringInputBuffer, sizeof(char) *
                                         inputSize);
        ReadInfo(*fd, &currentIslandGroupIslands, sizeof(int32_t));
        ReadInfo(*fd, &currentIslandGroupInhabitantIslands, sizeof(int32_t));

        if (strcmp(islandGroupName, stringInputBuffer) == 0)
        {
            found = true;
            continue;
        }
        char* currentIslandGroupName = (char*) malloc(
                inputSize * sizeof(char));
        strcpy(currentIslandGroupName, stringInputBuffer);
        WriteIslandGroup(tempFd, currentIslandGroupName,
                         currentIslandGroupIslands,
                         currentIslandGroupInhabitantIslands, inputSize);
        free(currentIslandGroupName);
    }
    close(*fd);
    *fd = tempFd;
    DeleteFile(filename);
    int renameReturn = rename(TEMP_FILE_NAME, filename);
    if (renameReturn != 0)
    {
        perror("Rename error");
    }
    return found;
}

int ChangeIslandGroupName(int fd, char* name, char* newName, int inputSize)
{
    if (SeekToGroupByName(fd, name, inputSize) != 0)
    {
        return -1;
    }
    WriteInfo(fd, newName, sizeof(char) *
                           inputSize);
    return 0;
}

int ChangeIslandGroupIslands(int fd, char* name, int islandGroupIslands,
                             int inputSize)
{
    if (SeekToGroupByName(fd, name, inputSize) != 0)
    {
        return -1;
    }
    lseek(fd, (int) sizeof(char) * inputSize, SEEK_CUR);
    WriteInfo(fd, &islandGroupIslands, sizeof(int32_t));
    int islandGroupInhabitantIslands;
    ReadInfo(fd, &islandGroupInhabitantIslands, sizeof (int32_t));
    if (islandGroupInhabitantIslands > islandGroupIslands)
    {
        ChangeIslandGroupInhabitantIslands(fd, name, islandGroupIslands,
                                           inputSize);
    }
    return 0;
}

int ChangeIslandGroupInhabitantIslands(int fd, char* name,
                                       int islandGroupInhIslands,
                                       int inputSize)
{
    if (SeekToGroupByName(fd, name, inputSize) != 0)
    {
        return -1;
    }
    lseek(fd, (int) sizeof(char) * inputSize, SEEK_CUR);
    int islandGroupIslands;
    ReadInfo(fd, &islandGroupIslands, sizeof(int32_t));
    if (islandGroupIslands < islandGroupInhIslands)
    {
        return -1;
    }
    WriteInfo(fd, &islandGroupInhIslands, sizeof(int32_t));
    return 0;
}

/*! \brief Prints island group, seeked in fd
 *
 *  \param fd         File descriptor
 *  \param inputSize  Maximal  size of island groups' name
 */
void PrintIslandGroup(int fd, int inputSize)
{
    char stringInputBuffer[MAX_INPUT_SIZE];
    int32_t currentIslandGroupIslands;
    int32_t currentIslandGroupInhabitantIslands;
    ReadInfo(fd, &stringInputBuffer, sizeof(char) *
                                     inputSize);
    ReadInfo(fd, &currentIslandGroupIslands, sizeof(int32_t));
    ReadInfo(fd, &currentIslandGroupInhabitantIslands, sizeof(int32_t));

    printf("Island %s, %d inhabitant islands of %d islands overall;\n",
           stringInputBuffer,
           currentIslandGroupInhabitantIslands,
           currentIslandGroupIslands);
}

void PrintIslandGroupByName(int fd, char* name, int inputSize)
{
    if (SeekToGroupByName(fd, name, inputSize) != 0)
    {
        printf("Island group not found!\n");
        return;
    }
    PrintIslandGroup(fd, inputSize);
}

void PrintIslandGroupsByIslands(int fd, int islands, int inputSize)
{
    int tempFd;
    if (PrepareNewFile(&tempFd, TEMP_FILE_NAME, inputSize) != 0)
    {
        printf("Something went wrong while creating temp file\n");
        return;
    }
    char currentIslandGroupName[MAX_INPUT_SIZE];
    int32_t currentIslandGroupIslands;
    int32_t currentIslandGroupInhabitantIslands;
    lseek(fd, sizeof(int32_t), SEEK_SET);
    while (lseek(fd, 0, SEEK_CUR) < GetFileSize(fd))
    {
        ReadInfo(fd, currentIslandGroupName, sizeof(char) *
                                             inputSize);
        ReadInfo(fd, &currentIslandGroupIslands, sizeof(int32_t));
        ReadInfo(fd, &currentIslandGroupInhabitantIslands, sizeof(int32_t));

        if (currentIslandGroupIslands == islands)
        {
            WriteIslandGroup(tempFd, currentIslandGroupName,
                             currentIslandGroupIslands,
                             currentIslandGroupInhabitantIslands, inputSize);
        }
    }
    PrintAllIslandGroups(tempFd, inputSize);
    close(tempFd);
    DeleteFile(TEMP_FILE_NAME);
}

void PrintIslandGroupsOnlyInhabited(int fd, int inputSize)
{
    int tempFd;
    if (PrepareNewFile(&tempFd, TEMP_FILE_NAME, inputSize) != 0)
    {
        printf("Something went wrong while creating temp file\n");
        return;
    }
    char currentIslandGroupName[MAX_INPUT_SIZE];
    int32_t currentIslandGroupIslands;
    int32_t currentIslandGroupInhabitantIslands;
    lseek(fd, sizeof(int32_t), SEEK_SET);
    while (lseek(fd, 0, SEEK_CUR) < GetFileSize(fd))
    {
        ReadInfo(fd, currentIslandGroupName, sizeof(char) *
                                             inputSize);
        ReadInfo(fd, &currentIslandGroupIslands, sizeof(int32_t));
        ReadInfo(fd, &currentIslandGroupInhabitantIslands, sizeof(int32_t));

        if (currentIslandGroupIslands == currentIslandGroupInhabitantIslands)
        {
            WriteIslandGroup(tempFd, currentIslandGroupName,
                             currentIslandGroupIslands,
                             currentIslandGroupInhabitantIslands, inputSize);
        }
    }
    PrintAllIslandGroups(tempFd, inputSize);
    close(tempFd);
    DeleteFile(TEMP_FILE_NAME);
}


void PrintAllIslandGroups(int fd, int inputSize)
{
    lseek(fd, sizeof(int32_t), SEEK_SET);
    while (lseek(fd, 0, SEEK_CUR) < GetFileSize(fd))
    {
        PrintIslandGroup(fd, inputSize);
    }
}

bool IsAnyUninhabited(int fd, int inputSize)
{
    int32_t currentIslandGroupInhabitantIslands;
    lseek(fd, sizeof(int32_t), SEEK_SET);
    while (lseek(fd, 0, SEEK_CUR) < GetFileSize(fd))
    {
        lseek(fd, sizeof(char) * inputSize + sizeof(int32_t), SEEK_CUR);
        ReadInfo(fd, &currentIslandGroupInhabitantIslands, sizeof(int32_t));

        if (currentIslandGroupInhabitantIslands == 0)
        {
            return true;
        }
    }
    return false;
}

int PrepareNewFile(int* fd, char* filename, int inputSize)
{
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int fdReturn;
    fdReturn = open(filename, O_RDWR | O_CREAT | O_TRUNC, mode);
    if (fdReturn < 0)
    {
        return -1;
    }
    *fd = fdReturn;
    WriteMeta(*fd, inputSize);
    return 0;
}

int OpenFile(int* fd, char* filename, int* inputSize)
{
    if (!FileExistCheck(filename))
    {
        return -1;
    }
    *fd = open(filename, O_RDWR);
    if (*fd < 0)
    {
        return -1;
    }
    if (ReadMeta(*fd, inputSize) != 0)
    {
        return -1;
    }
    return 0;
}