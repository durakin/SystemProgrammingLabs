#ifndef ISLANDGROUP_H
#define ISLANDGROUP_H

#include <string.h>
#include "LinkedList.h"


typedef struct
{
    char* name;
    int islands;
    int inhabitedIslands;
} IslandGroup;

void FreeIslandGroup(IslandGroup* objectIslandGroup);

void PrintIslandGroupLink(ListLink* object);

void PrintAllIslandGroups(ListLink* objectList);

ListLink* ListLinkIslandGroupsByIslands(ListLink* objectList, int islands);

bool AnyUnInhabitedIslandGroups(ListLink* objectList);

ListLink* FindIslandGroupLinkByName(ListLink* objectList, char* name);

ListLink* AddIslandGroup(ListLink* objectList, char* name, int islands,
                         int inhabitedIslands);

int DeleteIslandGroupByName_proper(ListLink** objectList, char* name);

int ChangeIslandGroupName(ListLink* objectLink, char* newName);

int ChangeIslandGroupIslands(ListLink* objectLink, int newIslands);

int ChangeInhabitedIslandGroupIslands(ListLink* objectLink,
                                      int newInhabitedIsland);

bool IslandGroupNameCheck(char* nameToCheck);

bool IslandsNumberCheck(int numberToCheck);

bool InhabitedIslandsNumberCheck(int numberToCheck);


#endif //ISLANDGROUP_H
