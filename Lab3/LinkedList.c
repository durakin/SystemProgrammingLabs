#include "LinkedList.h"


ListLink* ListLinkHead(ListLink* objectList)
{
    ListLink* position;
    position = objectList;
    if (objectList == NULL)
    {
        return NULL;
    }
    while (position->previous != NULL)
    {
        position = position->previous;
    }
    return position;
}

ListLink* ListLinkTail(ListLink* objectList)
{
    ListLink* position;
    position = objectList;
    if (position == NULL)
    {
        return NULL;
    }
    while (position->next != NULL)
    {
        position = position->next;
    }
    return position;
}

/*ListLink* ListLinkFindByCondition(ListLink* objectList,
                                  bool(* condition)(void*))
{
    ListLink* position;
    position = ListLinkHead(objectList);
    while (position != NULL)
    {
        if (condition(position))
        {
            break;
        }
        position = position->next;
    }
    return position;
}*/

void ListLinkSearchFromHead(ListLink* objectList, void* (* action)(void*))
{
    ListLink* position;
    position = ListLinkHead(objectList);
    while (position != NULL)
    {
        action(position);
        position = position->next;
    }
}

ListLink* ListLinkAdd(ListLink* objectList, void* content)
{
    ListLink* linkToAdd;
    linkToAdd = (ListLink*) malloc(sizeof(ListLink));
    linkToAdd->next = NULL;
    linkToAdd->previous = ListLinkTail(objectList);
    linkToAdd->content = content;

    if (linkToAdd->previous != NULL)
    {
        linkToAdd->previous->next = linkToAdd;
    }
    return linkToAdd;
}

ListLink* ListLinkDelete(ListLink* linkToDelete, void* (* freeContent)(void*))
{
    ListLink* linkToReturn;
    if (linkToDelete->next != NULL)
    {
        linkToDelete->next->previous = linkToDelete->previous;
    }
    linkToReturn = ListLinkHead(linkToDelete);
    if (linkToReturn != linkToDelete)
    {
        linkToDelete->previous->next = linkToDelete->next;
    }
    else
    {
        linkToReturn = linkToDelete->next;
    }
    freeContent(linkToDelete->content);
    free(linkToDelete);
    return linkToReturn;
}

void ListLinkSwap(ListLink* firstLink, ListLink* secondLink)
{
    void* contentBox;
    contentBox = firstLink->content;
    firstLink->content = secondLink->content;
    secondLink->content = contentBox;
}

int ListLinkSize(ListLink* objectList)
{
    ListLink* position;
    if (objectList == NULL)
    {
        return 0;
    }
    position = ListLinkHead(objectList);
    int size;
    size = 1;
    while (position->next != NULL)
    {
        size++;
        position = position->next;
    }
    return size;
}

void ListLinkBubbleSort(ListLink* objectList,
                        bool(* comparator)(void*, void*))
{
    ListLink* position;
    position = NULL;
    ListLink* index;
    index = NULL;
    for (position = ListLinkHead(objectList);
         position->next != NULL; position = position->next)
    {
        for (index = position->next;
             index != NULL; index = index->next)
        {
            if (comparator(index->content, position->content))
            {
                ListLinkSwap(position, index);
            }
        }
    }
}

void ListLinkFree(ListLink* objectList, void* (* freeContent)(void*))
{
    ListLink* position;
    position = ListLinkHead(objectList);
    while (position != NULL)
    {
        position = ListLinkDelete(position, freeContent);
    }
}
