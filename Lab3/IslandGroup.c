#include "IslandGroup.h"
#include <string.h>


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

/*void PrintIslandGroupsByIslands(ListLink* objectList, int islands)
{

};
*/

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
        islands < 1 ||inhabitedIslands > islands)
    {
        return NULL;
    }
    IslandGroup* newIslandGroup;
    newIslandGroup = (IslandGroup*) malloc(sizeof(IslandGroup));
    stpcpy(newIslandGroup->name, name);
    newIslandGroup->islands = islands;
    newIslandGroup->inhabitedIslands = inhabitedIslands;
    return ListLinkAdd(objectList, newIslandGroup);
}

int DeleteIslandGroupByName(ListLink** objectList, char* name)
{
    if (FindIslandGroupLinkByName(*objectList, name) == NULL) return -1;
    *objectList = ListLinkDelete(
            FindIslandGroupLinkByName(*objectList, name));
    return 0;
}
