#include <stdio.h>
#include "LinkedList.h"
#include "IslandGroup.h"


int main()
{
    ListLink* objectList = NULL;
    objectList = AddIslandGroup(objectList, "A", 10, 10);
    objectList = AddIslandGroup(objectList, "B", 10, 10);
    objectList = AddIslandGroup(objectList, "C", 10, 10);
    objectList = AddIslandGroup(objectList, "D", 10, 10);
    ChangeInhabitedIslandGroupIslands(FindIslandGroupLinkByName(objectList, "B"), 12);
    ChangeIslandGroupIslands(FindIslandGroupLinkByName(objectList, "A"), 8);
    PrintIslandGroupLink(FindIslandGroupLinkByName(objectList, "A"));
    PrintIslandGroupLink(FindIslandGroupLinkByName(objectList, "D"));
    printf("\n\n");
    DeleteIslandGroupByName(&objectList, "D");
    DeleteIslandGroupByName(&objectList,"0");
    PrintIslandGroupLink(FindIslandGroupLinkByName(objectList, "D"));
    PrintAllIslandGroups(objectList);
    ListLinkFree(objectList, (void*) FreeIslandGroup);
    return 0;
}
