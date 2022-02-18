/*
 * Defines functions for linked lists.
 * CSC 225, Assignment 8
 * Given code, Spring '21
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* Use this to allocate memory for arrays
(int *)malloc(sizeof(int)*/

/* lstcreate: Creates an empty linked list. */
List *lstcreate() {
    /* TODO: Complete this function, given no arguments:
     * ...return a pointer to a new, dynamically allocated List structure. */
    List *lstPtr;
    lstPtr = (List*)malloc(sizeof(List));
    (*lstPtr).head = NULL;
    (*lstPtr).size = 0;
    return lstPtr;
}

/* lstdestroy: Destroys an existing linked list. */
void lstdestroy(List *lst) {
    /* TODO: Complete this function, given:
     *  lst - A pointer to a List structure
     * ...deallocate all memory associated with "lst". */
    struct Node *tmp;
    while (lst->head != NULL)
    {
       tmp = lst->head;
       lst->head = lst->head->next;
       free(tmp);
    }
    free(lst);
}

/* lstsize: Computes the size of a linked list. */
unsigned int lstsize(List *lst) {
    /* TODO: Complete this function, given:
     *  lst - A pointer to a List structure
     * ...return the number of nodes in "lst". */    
    return lst->size;
}

/* lstget: Gets an element in a linked list at an index. */
void *lstget(List *lst, unsigned int idx) {
    /* TODO: Complete this function, given:
     *  lst - A pointer to a List structure
     *  idx - A non-negative index
     * ...return a pointer to element "idx" of "lst", NULL if "idx" outside
     * bounds [0, size - 1] */
    Node *tmphead = lst->head;
    int *dataPtr = NULL;
    int i;
    for (i=0; i<lstsize(lst); i++){
        if (i == idx){
            dataPtr = tmphead->data;
            return dataPtr;
        }
        tmphead = tmphead->next;
    }
    return NULL;
}

/* lstset: Sets an element in a linked list at an index. */
int lstset(List *lst, unsigned int idx, void *data) {
    /* TODO: Complete this function, given:
     *  lst  - A pointer to a List structure
     *  idx  - A non-negative index
     *  data - A pointer to a desired element
     * ...set element "idx" of "lst" to "data"; return 0 on success, 1 if "idx"
     * outside bounds [0, size - 1]. */
    Node *tmphead = lst->head;
    int i;
    for (i=0; i<lstsize(lst); i++){
        if (i == idx){
            tmphead->data = data;
            return 0;
        }
        tmphead = tmphead->next;
    }
    return 1;
}

/* lstadd: Adds an element to a linked list at an index. */
int lstadd(List *lst, unsigned int idx, void *data) {
    /* TODO: Complete this function, given:
     *  lst  - A pointer to a List structure
     *  idx  - A non-negative index
     *  data - A pointer to a desired element
     * ...add "data" as element "idx" of "lst", shifting existing elements as
     * necessary; return 0 on success, 1 if "idx" outside bounds [0, size]. */
    Node *tmphead = lst->head;
    Node *insert_node = (Node*) malloc(sizeof(Node));
    int i;
    insert_node->data = data;
    if (idx > lstsize(lst) && lst->head == NULL){
        free(insert_node);
        return 1;
    }

    if (idx == 0){
        insert_node->next = lst->head;
        lst->head = insert_node;
        lst->size++;
        return 0;
    }

    for (i=0; i <= (lstsize(lst)-1); i++){
        if (i == (lstsize(lst) -1) && i == idx-1){
            insert_node->next = NULL;
            tmphead->next = insert_node;
            lst->size++;
            return 0;
        }
        if (i == idx-1){
            insert_node->next = tmphead->next;
            tmphead->next = insert_node;        
            lst->size++;
            return 0;
        }
        if (i < (lstsize(lst) - 1))
            tmphead = tmphead->next;
    }
    free(insert_node);
    return 1;
}

/* lstremove: Removes an element from a linked list at an index. */
void *lstremove(List *lst, unsigned int idx) {
    /* TODO: Complete this function, given:
     *  lst  - A pointer to a List structure
     *  idx  - A non-negative index
     * ...remove element "idx" of "lst", shifting remaining elements as
     * necessary; return a pointer to the removed element, NULL if "idx"
     * outside bounds [0, size - 1]. */
    Node *tmphead, *prev;
    int *data;
    int i;
    tmphead = lst->head;
    if (idx >= lstsize(lst) && lst->head == NULL)
        return NULL;

    if (idx == 0){
        data = lst->head->data;
        prev = lst->head;
        lst->head = lst->head->next;
        free(prev);
        lst->size--;
        return data;
    }
    prev = tmphead;
    tmphead = tmphead->next;
    for (i=1; i <= (lstsize(lst) -1); i++){
        if (i == (lstsize(lst) -1) && i == idx){
            data = tmphead->data;
            free(prev->next);
            prev->next = NULL;
            lst->size--;
            return data;
        }
        if (i == idx){
            data = tmphead->data;
            prev->next = tmphead->next;
            free(tmphead);
            lst->size--;
            return data;
        }
        if (i <= (lstsize(lst) -1)){
            prev = tmphead;
            tmphead = tmphead->next;
        }
    }
    return NULL;
}

/* lsttoarr: Creates an array from a linked list. */
void **lsttoarr(List *lst) {
    /* TODO: Complete this function, given:
     *  lst  - A pointer to a List structure
     * ...return a dynamically allocated array of void pointers containing the
     * elements of "lst" in the same order. */
    void **arr = (void**) malloc(lst->size * sizeof(void*));
    int i;
    Node *tmphead = lst->head;

    for (i=0; i < (lstsize(lst)); i++){
        arr[i] = tmphead->data;
        tmphead = tmphead->next;
    }
    return arr;

}

/* arrtolst: Creates a linked list from an array. */
List *arrtolst(void **arr, unsigned int n) {
    /* TODO: Complete this function, given:
     *  arr  - An array of void pointers
     * ...return a pointer to a new, dynamically allocated list containing the
     * elements of "arr" in the same order. */
    List *lst = lstcreate();
    int i;

    for (i=0; i < n; i++){
        lstadd(lst, 0, arr[n - i - 1]);
    }
    return lst;

}
