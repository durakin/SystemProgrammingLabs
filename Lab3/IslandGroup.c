#include "IslandGroup.h"


void FreeIslandGroup(IslandGroup* objectIslandGroup)
{
    free(objectIslandGroup->name);
    free(objectIslandGroup);
}

void PrintIslandGroupLink(ListLink* object)
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

void PrintAllIslandGroups(ListLink* objectList)
{
    if (objectList != NULL)
    {
        ListLinkSearchFromHead(objectList, (void*) PrintIslandGroupLink);
    }
    else
    {
        printf("List is empty\n");
    }
}

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
            // ListLinkAdd(targetList, (IslandGroup*) position->content);
            targetList = AddIslandGroup(targetList, positionContent->name,
                                        positionContent->islands,
                                        positionContent->inhabitedIslands);
        }
        position = position->next;
    }
    return targetList;
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

ListLink* DeleteIslandGroupByName(ListLink* objectList, char* name)
{

    return ListLinkDelete(FindIslandGroupLinkByName(objectList, name),
                          (void*) FreeIslandGroup);
}

int DeleteIslandGroupByName_proper(ListLink** objectList, char* name)
{
    if (FindIslandGroupLinkByName(*objectList, name) == NULL)
    {
        return -1;
    }
    *objectList = ListLinkDelete(FindIslandGroupLinkByName(*objectList, name),
                                 (void*) FreeIslandGroup);
    return 0;
}

int ChangeIslandGroupName(ListLink* objectLink, char* newName)
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

int ChangeIslandGroupIslands(ListLink* objectLink, int newIslands)
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

int ChangeInhabitedIslandGroupIslands(ListLink* objectLink,
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
