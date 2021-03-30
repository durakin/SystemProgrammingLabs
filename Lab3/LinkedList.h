#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <malloc.h>
#include <stdbool.h>


typedef struct ListLink
{
    struct ListLink* previous;
    struct ListLink* next;
    void* content;
} ListLink;


ListLink* ListLinkHead(ListLink* objectList);

ListLink* ListLinkTail(ListLink* objectList);

ListLink* ListLinkAdd(ListLink* objectList, void* content);

ListLink*
ListLinkDelete(ListLink* linkToDelete, void* (* freeContent)(void*));

void ListLinkFree(ListLink* objectList, void* (* freeContent)(void*));

void ListLinkSearchFromHead(ListLink* objectList, void* (* action)(void*));


#endif //LINKEDLIST_H
