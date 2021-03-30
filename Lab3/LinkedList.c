/*! \file   LinkedList.c
 *  \brief  Implements functions of LinkedList.h
 */

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

void ListLinkFree(ListLink* objectList, void* (* freeContent)(void*))
{
    ListLink* position;
    position = ListLinkHead(objectList);
    while (position != NULL)
    {
        position = ListLinkDelete(position, freeContent);
    }
}
