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
/*! \brief Checks whether the file from the path exists or not.
 *
 * \param path Path to the file. The file can be local
 *
 *  \return 0 if exists else -1
 */
bool fileExistCheck(char* path)
{
    return (access(path, F_OK) == 0);
}


/*! \brief Calculates the file size
 *
 * \param fd File descriptor
 *
 *  \return File size
 */
int getFileSize(int fd)
{
    struct stat info;
    int fstatSuccess = fstat(fd, &info);
    if (fstatSuccess)
    {
        perror("Getting file info went wrong.");
    }
    printf("DEBUG Filesize is %d", (int) info.st_size);
    return (int) info.st_size;
}

/*! \brief Writes information in bytes from buffer into file. Similar to the function write() from <unistd.h>
 * but also outputs errors
 *
 * \param fd File descriptor
 * \param info Variable with information that will be loaded into file
 * \param size The number of bytes that will be loaded into file
 *
 *  \return -1 if something went wrong. Else the number of bytes that have been successfully loaded into file
 */
int writeInfo(int fd, void* info, size_t size)
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
    printf("DEBUG Written");
    return 0;
}

/*! \brief Writes meta information (size of one group) into beginning of the file (if the file is empty)
 *
 * \param fd File descriptor
 *
 *  \return Nothing
 */
int writeMeta(int fd, int32_t inputSize)
{
    lseek(fd, 0, SEEK_SET);
    if (getFileSize(fd) == 0)
    {
        return writeInfo(fd, &inputSize, sizeof(int32_t));
    }
    return -1;
}

/*! \brief Reads information from the file. Similar to the function read() from <unistd.h>
 * but also outputs errors
 *
 * \param fd File descriptor
 * \param info Variable with information that will be loaded into file
 * \param size The number of bytes that will be loaded into file
 *
 *  \return -1 if something went wrong. Else the number of bytes that have been successfully read from file
 */
int readInfo(int fd, void* info, size_t size)
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
 * \param fd File descriptor
 *
 *  \return Nothing
 */
int readMeta(int fd, int* inputSize)
{
    lseek(fd, 0, SEEK_SET);
    int readReturn;
    readReturn = readInfo(fd, (void*) inputSize, sizeof(int32_t));
    if (readReturn <= 0)
    {
        perror("Meta info error");
        return -1;
    }
    return 0;
}

/*! \brief Deletes the file from the working directory
 *
 * \param filename The name of file
 *
 *  \return Nothing
 */
int deleteFile(char* filename)
{
    int removeReturn = remove(filename);
    if (removeReturn != 0)
    {
        perror("File delete error");
        return -1;
    }
    return 0;
}

/*! \brief Deletes information about one group from the file. The group is identified by name
 *
 * \param fd File descriptor
 * \param groupName The name of a group
 *
 *  \return Is there such a group (0) or not (-1)
 */

void
writeIslandGroup(int fd, char* islandGroupName, int32_t islandGroupIslands,
                 int32_t islandGroupInhabitantIslands, int inputSize)
{
    lseek(fd, 0, SEEK_END);
    writeInfo(fd, islandGroupName, sizeof(char) *
                                   inputSize);
    printf("DEBUG name written");
    writeInfo(fd, (void*) &islandGroupIslands, sizeof(int32_t));
    printf("DEBUG islands written");
    writeInfo(fd, (void*) &islandGroupInhabitantIslands,
              sizeof(int32_t));
    printf("DEBUG inh islands written");
}

int addIslandGroup(int fd, char* islandGroupName, int32_t islandGroupIslands,
                   int32_t islandGroupInhabitantIslands, int inputSize)
{
    if (islandGroupInhabitantIslands > islandGroupIslands ||
        seekToGroupByName(fd, islandGroupName, inputSize) != -1)
    {
        return -1;
    }
    writeIslandGroup(fd, islandGroupName, islandGroupIslands,
                     islandGroupInhabitantIslands, inputSize);
    return 0;
}

int deleteGroupByName(int fd, char* islandGroupName, char* filename,
                      int inputSize)
{
    int fdBox = open("new", O_CREAT | O_WRONLY);
    writeMeta(fdBox, inputSize);

    char* currentIslandGroupName = (char*) malloc(inputSize * sizeof(char));
    int32_t currentIslandGroupIslands;
    int32_t currentIslandGroupInhabitantIslands;
    lseek(fd, sizeof(int32_t), SEEK_SET);

    bool found = false;
    while (lseek(fd, 0, SEEK_CUR) < getFileSize(fd))
    {
        readInfo(fd, currentIslandGroupName, sizeof(char) *
                                             inputSize);
        readInfo(fd, &currentIslandGroupIslands, sizeof(int32_t));
        readInfo(fd, &currentIslandGroupInhabitantIslands, sizeof(int32_t));

        if (strcmp(islandGroupName, currentIslandGroupName) == 0)
        {
            found = true;
            continue;
        }
        writeIslandGroup(fdBox, currentIslandGroupName,
                         currentIslandGroupIslands,
                         currentIslandGroupInhabitantIslands, inputSize);
    }

    close(fd);
    close(fdBox);

    deleteFile(filename);
    int renameReturn = rename("new", filename);
    if (renameReturn != 0)
    {
        perror("Rename error");
    }
    return found;
}

/*! \brief Moves the pointer in the file to one group
 *
 * \param fd File descriptor
 * \param groupName The name of a group
 *
 *  \return Is there such a group (0) or not (-1)
 */
int seekToGroupByName(int fd, char* groupName, int inputSize)
{
    lseek(fd, sizeof(int32_t), SEEK_SET);
    char currentGroupName[MAX_INPUT_SIZE];
    strcpy(currentGroupName, groupName);

    while (lseek(fd, 0, SEEK_CUR) < getFileSize(fd))
    {
        readInfo(fd, &currentGroupName, sizeof(char) *
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

/*! \brief Changes the name of one group in the file
 *
 * \param fd File descriptor
 * \param name The name of a group where a new name will be
 * \param newName A new name of the group
 *
 *  \return Is there such a group (0) or not (-1)
 */
int changeIslandGroupName(int fd, char* name, char* newName, int inputSize)
{
    if (seekToGroupByName(fd, name, inputSize) != 0)
    {
        return -1;
    }
    writeInfo(fd, newName, sizeof(char) *
                           inputSize);
    return 0;
}

/*! \brief Changes the students number of one group in the file
 *
 * \param fd File descriptor
 * \param name The name of a group where a new students number will be
 * \param newStudentsNumber A new students number of the group
 *
 *  \return Is there such a group (0) or not (-1)
 */
int changeIslandGroupIslands(int fd, char* name, int islandGroupIslands,
                             int inputSize)
{
    if (seekToGroupByName(fd, name, inputSize) != 0)
    {
        return -1;
    }
    lseek(fd, (int) sizeof(char) * inputSize, SEEK_CUR);
    writeInfo(fd, &islandGroupIslands, sizeof(int32_t));
    return 0;
}

/*! \brief Changes the females number of one group in the file
 *
 * \param fd File descriptor
 * \param groupName The name of a group where a new females number will be
 * \param newFemalesNumber A new females number of the group
 *
 *  \return Is there such a group (0) or not (-1)
 */
int changeIslandGroupInhabitantIslands(int fd, char* name,
                                       int islandGroupInhabitantIslands,
                                       int inputSize)
{
    if (seekToGroupByName(fd, name, inputSize) != 0)
    {
        return -1;
    }
    lseek(fd, (int) sizeof(char) * inputSize + (int) sizeof(int32_t),
          SEEK_CUR);
    writeInfo(fd, &islandGroupInhabitantIslands, sizeof(int32_t));
    return 0;
}

void printIslandGroup(int fd, int inputSize)
{
    char* currentIslandGroupName;
    currentIslandGroupName = (char*) malloc(inputSize * sizeof(char));
    char stringInputBuffer[MAX_INPUT_SIZE];
    int32_t currentIslandGroupIslands;
    int32_t currentIslandGroupInhabitantIslands;

    readInfo(fd, &stringInputBuffer, sizeof(char) *
                                     inputSize);
    puts(stringInputBuffer);
    strcpy(currentIslandGroupName, stringInputBuffer);
    readInfo(fd, &currentIslandGroupIslands, sizeof(int32_t));
    readInfo(fd, &currentIslandGroupInhabitantIslands, sizeof(int32_t));

    printf("Island %s, %d inhabitant islands of %d islands overall;\n",
           currentIslandGroupName,
           currentIslandGroupInhabitantIslands,
           currentIslandGroupIslands);
    free(currentIslandGroupName);
}

void printIslandGroupByName(int fd, char* name, int inputSize)
{
    if (seekToGroupByName(fd, name, inputSize) != 0)
    {
        printf("Island group not found!\n");
        return;
    }
    printIslandGroup(fd, inputSize);
}

void printAllIslandGroup(int fd, int inputSize)
{
    lseek(fd, sizeof(int32_t), SEEK_SET);
    while (lseek(fd, 0, SEEK_CUR) < getFileSize(fd))
    {
        printIslandGroup(fd, inputSize);
    }
}

bool isAnyUninhabitant(int fd, int inputSize)
{
    int32_t currentIslandGroupInhabitantIslands;
    lseek(fd, sizeof(int32_t), SEEK_SET);
    while (lseek(fd, 0, SEEK_CUR) < getFileSize(fd))
    {
        lseek(fd, sizeof(char) * inputSize + sizeof(int32_t), SEEK_CUR);
        readInfo(fd, &currentIslandGroupInhabitantIslands, sizeof(int32_t));

        if (currentIslandGroupInhabitantIslands == 0)
        {
            return true;
        }
    }
    return false;
}

// ⣿⣿⣷⡁⢆⠈⠕⢕⢂⢕⢂⢕⢂⢔⢂⢕⢄⠂⣂⠂⠆⢂⢕⢂⢕⢂⢕⢂⢕⢂
// ⣿⣿⣿⡷⠊⡢⡹⣦⡑⢂⢕⢂⢕⢂⢕⢂⠕⠔⠌⠝⠛⠶⠶⢶⣦⣄⢂⢕⢂⢕
// ⣿⣿⠏⣠⣾⣦⡐⢌⢿⣷⣦⣅⡑⠕⠡⠐⢿⠿⣛⠟⠛⠛⠛⠛⠡⢷⡈⢂⢕⢂
// ⠟⣡⣾⣿⣿⣿⣿⣦⣑⠝⢿⣿⣿⣿⣿⣿⡵⢁⣤⣶⣶⣿⢿⢿⢿⡟⢻⣤⢑⢂
// ⣾⣿⣿⡿⢟⣛⣻⣿⣿⣿⣦⣬⣙⣻⣿⣿⣷⣿⣿⢟⢝⢕⢕⢕⢕⢽⣿⣿⣷⣔
// ⣿⣿⠵⠚⠉⢀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣗⢕⢕⢕⢕⢕⢕⣽⣿⣿⣿⣿
// ⢷⣂⣠⣴⣾⡿⡿⡻⡻⣿⣿⣴⣿⣿⣿⣿⣿⣿⣷⣵⣵⣵⣷⣿⣿⣿⣿⣿⣿⡿
// ⢌⠻⣿⡿⡫⡪⡪⡪⡪⣺⣿⣿⣿⣿⣿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃
// ⠣⡁⠹⡪⡪⡪⡪⣪⣾⣿⣿⣿⣿⠋⠐⢉⢍⢄⢌⠻⣿⣿⣿⣿⣿⣿⣿⣿⠏⠈
// ⡣⡘⢄⠙⣾⣾⣾⣿⣿⣿⣿⣿⣿⡀⢐⢕⢕⢕⢕⢕⡘⣿⣿⣿⣿⣿⣿⠏⠠⠈
// ⠌⢊⢂⢣⠹⣿⣿⣿⣿⣿⣿⣿⣿⣧⢐⢕⢕⢕⢕⢕⢅⣿⣿⣿⣿⡿⢋⢜⠠⠈
// ⠄⠁⠕⢝⡢⠈⠻⣿⣿⣿⣿⣿⣿⣿⣷⣕⣑⣑⣑⣵⣿⣿⣿⡿⢋⢔⢕⣿⠠⠈
// ⠨⡂⡀⢑⢕⡅⠂⠄⠉⠛⠻⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⡿⢋⢔⢕⢕⣿⣿⠠⠈
// ⠄⠪⣂⠁⢕⠆⠄⠂⠄⠁⡀⠂⡀⠄⢈⠉⢍⢛⢛⢛⢋⢔⢕⢕⢕⣽⣿⣿⠠⠈

int prepareNewFile(int* fd, char* filename, int inputSize)
{
    int fdReturn;
    fdReturn = open(filename, O_RDWR | O_CREAT | O_TRUNC);
    if (fdReturn < 0)
    {
        return -1;
    }
    *fd = fdReturn;
    writeMeta(*fd, inputSize);
    return 0;
}

int openFile(int* fd, char* filename, int* inputSize)
{
    if (!fileExistCheck(filename))
    {
        return -1;
    }
    *fd = open(filename, O_RDWR);
    if (fd < 0)
    {
        return -1;
    }
    if (readMeta(*fd, inputSize) != 0)
    {
        return -1;
    }
    return 0;
}