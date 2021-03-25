#ifndef ISLANDGROUP_H
#define ISLANDGROUP_H

#include "LinkedList.h"


typedef struct
{
    char name[200];
    int islands;
    int inhabitedIslands;
} IslandGroup;


void PrintIslandGroupLink(ListLink* object);

void PrintAllIslandGroups(ListLink* objectList);

// void PrintIslandGroupsByIslands(ListLink* objectList, int islands);

bool AnyUnInhabitedIslandGroups(ListLink* objectList);

ListLink* FindIslandGroupLinkByName(ListLink* objectList, char* name);

ListLink* AddIslandGroup(ListLink* objectList, char* name, int islands,
                         int inhabitedIslands);

int DeleteIslandGroupByName(ListLink** objectList, char* name);


#endif //ISLANDGROUP_H
