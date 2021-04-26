/*! \file   FileIO.h
 *  \brief  Header file of functions working with files keeping info of
 *  island groups.
 */

#ifndef FILEIO_H
#define FILEIO_H
#include <inttypes.h>
#include <stdbool.h>


/*! \brief Checks consistence of information and uniqueness of island group's
 *  name and saves it to file
 *
 *  \param fd                     File descriptor
 *  \param islandGroupName        Name of island group
 *  \param islandGroupIslands     Overall number of islands in group
 *  \param islandGroupInhIslands  Number of inhabitant islands in group
 *  \param inputSize              Maximal size of island groups' name
 *
 *  \return 0 on success, -1 otherwise
 */
int AddIslandGroup(int fd, char* islandGroupName, int32_t islandGroupIslands,
                   int32_t islandGroupInhabitantIslands, int inputSize);

/*! \brief Deletes island group from list by name
 *
 *  \details Copies file content into new file, skipping island group to
 *  delete, renames it, and deletes old file.
 *
 *  \param fd               Pointer to file descriptor
 *  \param islandGroupName  Name of island group to delete
 *  \param filename         Name of save file
 *  \param inputSize        Maximal size of island groups' name
 *
 *  \return true if something was deleted, false otherwise
 */
bool DeleteGroupByName(int* fd, char* islandGroupName, char* filename,
                       int inputSize);

/*! \brief Changes the name of one group in the file
 *
 *  \param fd         File descriptor
 *  \param name       Name of the group to rename
 *  \param newName    New name of the group
 *  \param inputSize  Maximal size of island groups' name
 *
 *  \return 0 if group was found, -1 otherwise
 */
int ChangeIslandGroupName(int fd, char* name, char* newName, int inputSize);

/*! \brief Changes overall number of islands in group by name
 *
 *  \details If new overall number of island groups is smaller than old
 *  inhabitant - also changes number of inhabitant to new overall number
 *  of islands.
 *
 *  \param fd                  File descriptor
 *  \param name                Name of the group to change islands number
 *  \param islandGroupIslands  New number of islands
 *  \param inputSize           Maximal  size of island groups' name
 *
 *  \return 0 if island group was found and changed, -1 otherwise
 */
int ChangeIslandGroupIslands(int fd, char* name, int islandGroupIslands,
                             int inputSize);

/*! \brief Changes number of inhabitant islands in group by name
 *
 *  \details If new number of inhabitant islands in group is smaller than old
 *  overall number of islands - doesn't change anything.
 *
 *  \param fd                     File descriptor
 *  \param name                   Name of the group to change islands number
 *  \param islandGroupInhIslands  New number of inhabitant islands
 *  \param inputSize              Maximal  size of island groups' name
 *
 *  \return 0 if island group was found and changed, -1 otherwise
 */
int ChangeIslandGroupInhabitantIslands(int fd, char* name,
                                       int islandGroupInhIslands,
                                       int inputSize);

/*! \brief Prints island group, by name
 *
 *  \param fd         File descriptor
 *  \param char       Name of group to print
 *  \param inputSize  Maximal  size of island groups' name
 */
void PrintIslandGroupByName(int fd, char* name, int inputSize);

/*! \brief Prints island groups, by number of islands
 *
 *  \details Creates temp list of suitable islands, prints it and deletes
 *
 *  \param fd         File descriptor
 *  \param islands    Required number of islands
 *  \param inputSize  Maximal  size of island groups' name
 */
void PrintIslandGroupsByIslands(int fd, int islands, int inputSize);

void PrintIslandGroupsOnlyInhabited(int fd, int inputSize);

/*! \brief Prints island groups, by number of islands
 *
 *  \details Creates temp list of suitable islands, prints it and deletes
 *
 *  \param fd         File descriptor
 *  \param islands    Required number of islands
 *  \param inputSize  Maximal  size of island groups' name
 */
void PrintAllIslandGroups(int fd, int inputSize);

/*! \brief Checks if any island group in file hasn't any inhabitant island
 *
 *  \param fd         File descriptor
 *  \param inputSize  Maximal  size of island groups' name
 *
 *  \return true if any island group in file hasn't any inhabitant island,
 *  false otherwise
 */
bool IsAnyUninhabited(int fd, int inputSize);

/*! \brief Prepares new file for saving island groups info
 *
 *  \details Creates file with name filename, opens it putting descriptor
 *  into *fd by pointer, puts meta into this file.
 *
 *  \param fd         Pointer to file descriptor
 *  \param filename   Name of save file
 *  \param inputSize  Maximal size of island groups' name
 *
 *  \return 0 on success, -1 otherwise.
 */
int PrepareNewFile(int* fd, char* filename, int inputSize);

/*! \brief Opens file and reads meta
 *
 *  \details Opens file with name filename, putting descriptor
 *  into *fd by pointer, reads meta into this file putting it into *inputSize.
 *  Doesn't provide any check of data in file.
 *
 *  \param fd         Pointer to file descriptor
 *  \param filename   Name of save file
 *  \param inputSize  Pointer to put maximal size of island groups' name
 *
 *  \return 0 on success, -1 otherwise.
 */
int OpenFile(int* fd, char* filename, int* inputSize);


#endif //FILEIO_H
