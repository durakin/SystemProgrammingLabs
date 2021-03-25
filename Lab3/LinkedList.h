//
// Created by Albert Nepomnyashiy on 3/25/2021.
//

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

ListLink* ListLinkDelete(ListLink* linkToDelete);

void ListLinkSwap(ListLink* firstLink, ListLink* secondLink);

int ListLinkSize(ListLink* objectList);

void ListLinkBubbleSort(ListLink* objectList,
                        bool(* comparator)(void*, void*));

void ListLinkFree(ListLink* objectList);

void ListLinkSearchFromHead(ListLink* objectList, void* (*action) (void*));


#endif //LINKEDLIST_H
