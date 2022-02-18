/*
 * Defines structures and prototypes for linked lists.
 * CSC 225, Assignment 8
 * Given code, Spring '21
 * NOTE: Do not alter this file.
 */

/* Node: Represents a single element in a linked list. */
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

/* List: Represents a linked list. */
typedef struct List {
    Node *head;
    unsigned int size;
} List;

List *lstcreate();
void lstdestroy(List *);
unsigned int lstsize(List *);
void *lstget(List *, unsigned int);
int lstset(List *, unsigned int, void *);
int lstadd(List *, unsigned int, void *);
void *lstremove(List *, unsigned int);
void **lsttoarr(List *);
List *arrtolst(void **, unsigned int);
