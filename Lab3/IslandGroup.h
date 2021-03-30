/*! \file   IslandGroup.h
 *  \brief  Header file of struct IslandGroup and functions for storing it
 *  as a linked list content
 */

#ifndef ISLANDGROUP_H
#define ISLANDGROUP_H

#include <string.h>
#include "LinkedList.h"


/*! \struct IslandGroup
 *  \brief island group struct
 *
 *  \details Keeps information about island group's name, number of islands
 *  and inhabited islands
 */
typedef struct
{
    /*!
     * Name of island group
     */
    char* name;
    /*!
     * Overall number of islands
     */
    int islands;
    /*!
     * Number of inhabited islands
     */
    int inhabitedIslands;
} IslandGroup;

/*! \brief Frees memory allocated for island group
 *
 *  \param objectIslandGroup pointer to IslandGroup object.
 */
void FreeIslandGroup(IslandGroup* objectIslandGroup);

/*! \brief Prints info about all island groups in list
 *
 *  \details Prints content of every link in linked list as if it contains
 *  IslandGroup object.
 *
 *  \param objectList Pointer to any link of list to print.
 */
void PrintAllIslandGroups(ListLink* objectList);

/*! \brief Prints info about island group, found in list by its name
 *
 *  \param objectList Pointer to any link of list to search.
 *  \param name Name of island group to find and print
 */
void PrintIslandGroup(ListLink* objectList, char* name);

/*! \brief Prints info about all island groups with specific number of islands
 *
 *  \param objectList Pointer to any link of list to search.
 *  \param requiredIslands Number of islands of groups to print
 */
void PrintIslandGroupsByIslands(ListLink* objectList, int requiredIslands);

/*! \brief Checks if there is any inhabited island group in list
 *
 *  \details Checks if there is any island group that has 0 inhabited
 *  islands in list.
 *  \param objectList Pointer to any link of list to search.
 *
 *  \return Boolean true if there is any island group that has 0 inhabited
 *  islands in list, false - otherwise.
 */
bool AnyUnInhabitedIslandGroups(ListLink* objectList);

/*! \brief Adds islands group in list by all its params
 *
 *  \details Checks if there is no any island group that has same name, or
 *  information about islands is incorrect. Creates a new IslandGroup and
 *  adds link with such content to the list if it's correct or returns NULL.
 *  Possible memory leak: allocates memory for new IslandsGroup and Link
 *  containing it.
 *
 *  \param objectList Pointer to any link of list to add new IslandGroup.
 *  \param name Name of new island group.
 *  \param islands Overall number of islands in new islands group.
 *  \param inhabitedIslands Number of inhabited islands in new islands group.
 *
 *  \return Pointer to added link or NULL if not added
 */
ListLink* AddIslandGroup(ListLink* objectList, char* name, int islands,
                         int inhabitedIslands);

/*! \brief Deletes island group from list by name
 *
 *  \details Removes linked list link containing island group with such name.
 *  Frees its content and it.
 *  Changes *objectList to the head of new list to avoid loosing pointers to
 *  list.
 *
 *  \param objectList Pointer to pointer to any link of list to search.
 *  \param name Name of island group to delete
 *
 *  \return 0 on success, -1 otherwise.
 */
int DeleteIslandGroup(ListLink** objectList, char* name);

/*! \brief Changes name of island group to new founding it in list by its
 *  original name
 *
 *  \details Finds island group in list by its name and changes its name
 *  to new, checking if it will be unique.
 *
 *  \param objectList Pointer to pointer to any link of list to search.
 *  \param name Name of island group to modify
 *  \param newName New name of island group to be modified
 *
 *  \return 0 on success, -1 otherwise.
 */
int ChangeIslandGroupName(ListLink* objectList, char* name, char* newName);

/*! \brief Changes overall number of island group to new founding it in list
 *  by its original name
 *
 *  \details Finds island group in list by its name and changes its overall
 *  islands number to new. If new overall number is bigger than original
 *  inhabited islands number - both will be changed to new number.
 *
 *  \param objectList Pointer to pointer to any link of list to search.
 *  \param name Name of island group to modify
 *  \param newIslands New overall number of islands
 *
 *  \return 0 on success, -1 otherwise.
 */
int
ChangeIslandGroupIslands(ListLink* objectList, char* name, int newIslands);

/*! \brief Changes number of inhabited island group to new founding it in list
 *  by its original name
 *
 *  \details Finds island group in list by its name and changes its inhabited
 *  islands number to new. If new number is bigger than overall islands
 *  number, leaves object unchanged and returns -1.
 *
 *  \param objectList Pointer to pointer to any link of list to search.
 *  \param name Name of island group to modify
 *  \param newInhabitedIslands New  number of inhabited islands
 *
 *  \return 0 on success, -1 otherwise.
 */
int ChangeIslandGroupInhIslands(ListLink* objectList, char* name,
                                int newInhabitedIslands);

/*! \brief Checks if string can be a name for island group
 *
 *  \param nameToCheck string to check.
 *  \return true if string can be a name for island group
 *  false - otherwise
 */
bool IslandGroupNameCheck(char* nameToCheck);

/*! \brief Checks if number can be an overall number of islands of island
 *  group
 *
 *  \param intToCheck number to check.
 *  \return true if number can be an overall number of islands of island
 *  group
 *  false - otherwise
 */
bool IslandsNumberCheck(int numberToCheck);

/*! \brief Checks if number can be a number of inhabited islands of island
 *  group
 *
 *  \param numberToCheck number to check.
 *  \return true if number can be a number of inhabited islands of island
 *  group
 *  false - otherwise
 */
bool InhabitedIslandsNumberCheck(int numberToCheck);


#endif //ISLANDGROUP_H
