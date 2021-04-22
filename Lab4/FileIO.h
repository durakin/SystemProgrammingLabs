#ifndef FILEIO_H
#define FILEIO_H

#include <inttypes.h>
#include <unistd.h>
#include <stdbool.h>

/*! \brief Checks whether the file from the path exists or not.
 *
 * \param path Path to the file. The file can be local
 *
 *  \return 0 if exists else -1
 */
bool fileExistCheck(char* path);

/*! \brief Calculates the file size
 *
 * \param fd File descriptor
 *
 *  \return File size
 */
int getFileSize(int fd);

/*! \brief Writes information in bytes from buffer into file. Similar to the function write() from <unistd.h>
 * but also outputs errors
 *
 * \param fd File descriptor
 * \param info Variable with information that will be loaded into file
 * \param size The number of bytes that will be loaded into file
 *
 *  \return -1 if something went wrong. Else the number of bytes that have been successfully loaded into file
 */
int writeInfo(int fd, void* info, size_t size);

/*! \brief Writes meta information (size of one group) into beginning of the file (if the file is empty)
 *
 * \param fd File descriptor
 *
 *  \return Nothing
 */
int writeMeta(int fd, int32_t inputSize);

/*! \brief Reads information from the file. Similar to the function read() from <unistd.h>
 * but also outputs errors
 *
 * \param fd File descriptor
 * \param info Variable with information that will be loaded into file
 * \param size The number of bytes that will be loaded into file
 *
 *  \return -1 if something went wrong. Else the number of bytes that have been successfully read from file
 */
int readInfo(int fd, void* info, size_t size);

/*! \brief Reads meta information (size of one group) from the file
 *
 * \param fd File descriptor
 *
 *  \return Nothing
 */
int readMeta(int fd, int* inputSize);

/*! \brief Deletes the file from the working directory
 *
 * \param filename The name of file
 *
 *  \return Nothing
 */

int addIslandGroup(int fd, char* islandGroupName, int32_t islandGroupIslands,
                   int32_t islandGroupInhabitantIslands, int inputSize);


int deleteFile(char* filename);

/*! \brief Deletes information about one group from the file. The group is identified by name
 *
 * \param fd File descriptor
 * \param groupName The name of a group
 *
 *  \return Is there such a group (0) or not (-1)
 */
int deleteGroupByName(int fd, char* islandGroupName, char* filename,
                      int inputSize);

/*! \brief Moves the pointer in the file to one group
 *
 * \param fd File descriptor
 * \param groupName The name of a group
 *
 *  \return Is there such a group (0) or not (-1)
 */
int seekToGroupByName(int fd, char* groupName, int inputSize);

/*! \brief Changes the name of one group in the file
 *
 * \param fd File descriptor
 * \param name The name of a group where a new name will be
 * \param newName A new name of the group
 *
 *  \return Is there such a group (0) or not (-1)
 */
int changeIslandGroupName(int fd, char* name, char* newName, int inputSize);

/*! \brief Changes the students number of one group in the file
 *
 * \param fd File descriptor
 * \param name The name of a group where a new students number will be
 * \param newStudentsNumber A new students number of the group
 *
 *  \return Is there such a group (0) or not (-1)
 */
int changeIslandGroupIslands(int fd, char* name, int islandGroupIslands,
                             int inputSize);

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
                                       int inputSize);

void printIslandGroup(int fd, int inputSize);

void printIslandGroupByName(int fd, char* name, int inputSize);

void printAllIslandGroup(int fd, int inputSize);

bool isAnyUninhabitant(int fd, int inputSize);

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

int prepareNewFile(int* fd, char* filename, int inputSize);

int openFile(int* fd, char* filename, int* inputSize);

#endif //FILEIO_H
