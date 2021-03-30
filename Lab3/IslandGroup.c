/*! \file   IslandGroup.c
 *  \brief  Implements functions of IslandGroup.h
 */

#include "IslandGroup.h"

/*! \brief Finds islands group in list by its name
 *
 *
 *  \param objectList Pointer to any link of list to find island group.
 *  \param name Name of island group to find.
 *
 *  \return Pointer to link containing required island group or NULL if
 *  not found
 */
ListLink* FindIslandGroupLinkByName(ListLink* objectList, char* name)
{
    ListLink* position;
    position = ListLinkHead(objectList);
    while (position != NULL)
    {
        if (strcmp(((IslandGroup*) position->content)->name, name) == 0)
        {
            break;
        }
        position = position->next;
    }
    return position;
}

/*! \brief Creates a linked list with deep copies of island groups from
 *  other list, having specific overall number of islands
 *
 *  \details Possible memory leak: allocates memory for new list and its link
 *  and contents.
 *
 *  \param objectList Pointer to any link of list to find island groups.
 *  \param islands Required number of islands
 *
 *  \return Pointer to head link of new linked list
 */
ListLink* ListLinkIslandGroupsByIslands(ListLink* objectList, int islands)
{
    ListLink* targetList;
    targetList = NULL;
    ListLink* position;
    position = ListLinkHead(objectList);
    IslandGroup* positionContent;
    while (position != NULL)
    {
        positionContent = (IslandGroup*) position->content;
        if (positionContent->islands == islands)
        {
            targetList = AddIslandGroup(targetList, positionContent->name,
                                        positionContent->islands,
                                        positionContent->inhabitedIslands);
        }
        position = position->next;
    }
    return ListLinkHead(targetList);
}

/*! \brief Prints info about island group stored in link of linked list
 *
 *  \param object Pointer to link containing island group to print.
 */
void PrintIslandGroupByLink(ListLink* object)
{
    if (object == NULL)
    {
        printf("No such island group\n");
        return;
    }
    IslandGroup* objectContent = (IslandGroup*) (object->content);
    printf("Island group %s, %d inhabited islands of %d islands\n",
           objectContent->name, objectContent->inhabitedIslands,
           objectContent->islands);
}

/*! \brief Changes name of island group stored in link of linked list
 *
 *  \param objectLink Pointer to link of list containing island group to
 *  modify.
 *  \param newName New name of island group to be modified
 *
 *  \return 0 on success, -1 otherwise.
 */
int ChangeIslandGroupNameByLink(ListLink* objectLink, char* newName)
{
    if (objectLink == NULL ||
        FindIslandGroupLinkByName(objectLink, newName) != NULL)
    {
        return -1;
    }
    free(((IslandGroup*) objectLink->content)->name);
    ((IslandGroup*) objectLink->content)->name = newName;
    return 0;
}

/*! \brief Changes overall number of island group to new by pointer on linked
 *  list link, containing it
 *
 *  \details If new overall number is bigger than original
 *  inhabited islands number - both will be changed to new number.
 *
 *  \param objectLink Pointer to link of list containing island group to
 *  modify.
 *  \param newIslands New overall number of islands
 *
 *  \return 0 on success, -1 otherwise.
 */
int ChangeIslandGroupIslandsByLink(ListLink* objectLink, int newIslands)
{
    if (objectLink == NULL)
    {
        return -1;
    }
    IslandGroup* objectContent;
    objectContent = (IslandGroup*) objectLink->content;
    if (newIslands < objectContent->inhabitedIslands)
    {
        objectContent->inhabitedIslands = newIslands;
    }
    objectContent->islands = newIslands;
    return 0;
}

/*! \brief Changes number of inhabited islands in island group to new by
 *  pointer on linked list link, containing it
 *
 *  \details If new number is bigger than overall islands
 *  number, leaves object unchanged and returns -1.
 *
 *  \param objectLink Pointer to link of list containing island group to
 *  modify.
 *  \param newInhabitedIslands New  number of inhabited islands
 *
 *  \return 0 on success, -1 otherwise.
 */
int ChangeInhabitedIslandGroupIslandsByLink(ListLink* objectLink,
                                            int newInhabitedIsland)
{
    if (objectLink == NULL)
    {
        return -1;
    }
    IslandGroup* objectContent;
    objectContent = (IslandGroup*) objectLink->content;
    if (newInhabitedIsland > objectContent->islands)
    {
        return -1;
    }
    objectContent->inhabitedIslands = newInhabitedIsland;
    return 0;
}

void FreeIslandGroup(IslandGroup* objectIslandGroup)
{
    free(objectIslandGroup->name);
    free(objectIslandGroup);
}

void PrintAllIslandGroups(ListLink* objectList)
{
    if (objectList != NULL)
    {
        ListLinkSearchFromHead(objectList, (void*) PrintIslandGroupByLink);
    }
    else
    {
        printf("List is empty\n");
    }
}

void PrintIslandGroup(ListLink* objectList, char* name)
{
    PrintIslandGroupByLink(FindIslandGroupLinkByName(objectList, name));
}

void PrintIslandGroupsByIslands(ListLink* objectList, int requiredIslands)
{
    ListLink* tempSubList;
    tempSubList = ListLinkIslandGroupsByIslands(objectList,
                                                requiredIslands);
    PrintAllIslandGroups(tempSubList);
    ListLinkFree(tempSubList, (void*) FreeIslandGroup);
}

bool AnyUnInhabitedIslandGroups(ListLink* objectList)
{
    ListLink* position;
    position = ListLinkHead(objectList);
    while (position != NULL)
    {
        if (((IslandGroup*) position->content)->inhabitedIslands == 0)
        {
            return true;
        }
        position = position->next;
    }
    return false;
}

ListLink* AddIslandGroup(ListLink* objectList, char* name, int islands,
                         int inhabitedIslands)
{
    if (FindIslandGroupLinkByName(objectList, name) != NULL ||
        islands < 1 || inhabitedIslands > islands)
    {
        return NULL;
    }
    IslandGroup* newIslandGroup;
    newIslandGroup = (IslandGroup*) malloc(sizeof(IslandGroup));
    newIslandGroup->name = (char*) malloc(sizeof(name));
    stpcpy(newIslandGroup->name, name);
    newIslandGroup->islands = islands;
    newIslandGroup->inhabitedIslands = inhabitedIslands;
    return ListLinkAdd(objectList, newIslandGroup);
}

int DeleteIslandGroup(ListLink** objectList, char* name)
{
    if (FindIslandGroupLinkByName(*objectList, name) == NULL)
    {
        return -1;
    }
    *objectList = ListLinkDelete(FindIslandGroupLinkByName(*objectList, name),
                                 (void*) FreeIslandGroup);
    return 0;
}

int ChangeIslandGroupName(ListLink* objectList, char* name, char* newName)
{
    return ChangeIslandGroupNameByLink(
            FindIslandGroupLinkByName(objectList, name),
            newName);
}

int ChangeIslandGroupIslands(ListLink* objectList, char* name, int newIslands)
{
    return ChangeIslandGroupIslandsByLink(
            FindIslandGroupLinkByName(objectList, name), newIslands);
}

int ChangeIslandGroupInhIslands(ListLink* objectList, char* name,
                                int newInhabitedIslands)
{
    return ChangeInhabitedIslandGroupIslandsByLink(
            FindIslandGroupLinkByName(objectList, name), newInhabitedIslands);
}

bool IslandGroupNameCheck(char* nameToCheck)
{
    for (int i = 0; i < strlen(nameToCheck); i++)
    {
        if (nameToCheck[i] >= '0' && nameToCheck[i] <= '9' ||
            nameToCheck[i] >= 'A' && nameToCheck[i] <= 'Z' ||
            nameToCheck[i] >= 'a' && nameToCheck[i] <= 'z')
        {
            return true;
        }
    }
    return false;
}

bool IslandsNumberCheck(int numberToCheck)
{
    return numberToCheck > 0;
}

bool InhabitedIslandsNumberCheck(int numberToCheck)
{
    return numberToCheck >= 0;
}
