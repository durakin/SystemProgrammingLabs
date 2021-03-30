/*! \file   LinkedList.h
 *  \brief  Header file of struct LinkedList and functions for it.
 *  \author https://github.com/durakin
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <malloc.h>
#include <stdbool.h>

/*! \struct ListLink
 *  \brief Struct for link of listed link
 *
 *  \details Keeps pointers to previous and next elements of list and
 *  pointer to content of link.
 */
typedef struct ListLink
{
    /*!
     * Pointer to the previous element
     */
    struct ListLink* previous;
    /*!
     * Pointer to the next element
     */
    struct ListLink* next;
    /*!
     * Pointer to the content
     */
    void* content;
} ListLink;


/*! \brief Finds head of listed link by pointer on any link of list
 *
 *  \param objectList Pointer to any link of list to find a head
 *
 *  \return Pointer to head of linked list
 */
ListLink* ListLinkHead(ListLink* objectList);

/*! \brief Finds tail of listed link by pointer on any link of list
 *
 *  \param objectList Pointer to any link of list to find a tail
 *
 *  \return Pointer to tail of linked list
 */
ListLink* ListLinkTail(ListLink* objectList);

/*! \brief Adds new element to the end of linked list
 *
 *  \param objectList Pointer to any link of list to add new element
 *
 *  \return Pointer to added element of linked list
 */
ListLink* ListLinkAdd(ListLink* objectList, void* content);

/*! \brief Deletes element of linked list by pointer
 *
 * \details Calls freeContent() of link to delete for freeing a content, then
 * frees link itself.
 *
 *  \param linkToDelete Pointer to the link to delete
 *  \param freeContent Function to free content of linked list
 *
 *  \return Head of a new list
 */
ListLink*
ListLinkDelete(ListLink* linkToDelete, void* (* freeContent)(void*));

/*! \brief Delete list link and free memory
 *
 * \details Calls ListLinkDelete() of every link of linked list
 *
 *  \param linkToDelete Pointer to the link to delete
 *  \param freeContent Function to free content of linked list
 *
 *  \return Head of a new list
 */
void ListLinkFree(ListLink* objectList, void* (* freeContent)(void*));

/*! \brief Calls some function from every link of linked list
 *
 *  \details Calls action() of every link of linked list
 *
 *  \param objectList Pointer to any link of linked list to search
 *  \param action Function to call of linked list elements
 */
void ListLinkSearchFromHead(ListLink* objectList, void* (* action)(void*));


#endif //LINKEDLIST_H
