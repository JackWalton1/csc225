/*
 * Tests functions for linked lists.
 * CSC 225, Assignment 8
 * Given tests, Spring '21
 */

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

/* test01empty: Tests empty lists. */

void test01empty() {
    List *lst = lstcreate();
    int data1 = 1;
    assert(lst != NULL);
    assert(lst->head == NULL);
    assert(lst->size == 0);
    assert(lstget(lst, 0) == NULL);
    assert(lstremove(lst, 0) == NULL);
    assert(lstadd(lst, 1, &data1) == 1);
    assert(lstset(lst, 0, &data1) == 1);

    lstdestroy(lst);
}

/* test02add: Tests adding to lists. */
void test02add() {
    List *lst = lstcreate();
    int data1 = 1, data2 = 2;
    lstadd(lst, 0, &data1);
    lstadd(lst, 1, &data2);

    assert(lst->head != NULL);
    assert(lst->head->data == &data1);
    assert(lst->head->next->data == &data2);
    assert(lst->head->next->next == NULL);
    assert(lst->size == 2);

    assert(lstadd(lst, 4, &data1) == 1);

    lstdestroy(lst);
}

/* test03remove: Tests removing from lists. */
void test03remove_0() {
    List *lst = lstcreate();
    int data1 = 1, data2 = 2;

    lstadd(lst, 0, &data1);
    lstadd(lst, 1, &data2);
    lstremove(lst, 0);

    assert(lst->head != NULL);
    assert(lst->head->data == &data2);
    assert(lst->size == 1);

    assert(lst->head->next == NULL);

    lstdestroy(lst);
}

void test03remove_1() {
    List *lst = lstcreate();
    int data1 = 1, data2 = 2;

    lstadd(lst, 0, &data1);
    lstadd(lst, 1, &data2);
    assert(lstremove(lst, 1) == &data2);

    assert(lst->head != NULL);
    assert(lst->head->data == &data1);
    assert(lst->size == 1);
    assert(lst->head->next == NULL);

    lstdestroy(lst);
}

void test03remove_2() {
    List *lst = lstcreate();
    int data1 = 1, data2 = 2, data3 = 3;

    lstadd(lst, 0, &data1);
    lstadd(lst, 1, &data2);
    lstadd(lst, 2, &data3);
    assert(lstremove(lst, 1) == &data2);

    assert(lst->head != NULL);
    assert(lst->head->data == &data1);
    assert(lst->size == 2);
    assert(lst->head->next->data == &data3);
    assert(lst->head->next->next == NULL);

    lstdestroy(lst);
}

void test04size() {
    List *lst = lstcreate();
    int data1 = 1, data2 = 2;

    assert(lstsize(lst) == 0);
    lstadd(lst, 0, &data1);
    lstadd(lst, 1, &data2);
    assert(lstsize(lst) == 2);

    lstdestroy(lst);
}

void test05getset() {
    List *lst = lstcreate();
    int data1 = 1, data2 = 2, data3 = 3, data4 = 4;
    lstadd(lst, 0, &data1);
    lstadd(lst, 1, &data2);
    lstadd(lst, 2, &data4);
    lstset(lst, 1, &data3);
    assert((lst->head->next->data) == &data3);
    assert(lstget(lst, 1) == &data3);
    assert(lstget(lst, 2) == &data4);

    lstdestroy(lst);
}

void test06lsttoarr() {
    List *lst = lstcreate();
    void **arr = NULL;
    int data1 = 1, data2 = 2;
    lstadd(lst, 0, &data1);
    lstadd(lst, 1, &data2);
    arr = lsttoarr(lst);

    assert(arr[0] ==  &data1);
    assert(arr[1] == &data2);

    free(arr);
    lstdestroy(lst);
}

void test07arrtolst() {
    List *lst = lstcreate();
    void **arr = NULL;
    int data1 = 1, data2 = 2;
    lstadd(lst, 0, &data1);
    lstadd(lst, 1, &data2);
    arr = lsttoarr(lst);
    lstdestroy(lst);

    lst = arrtolst(arr, 2);
    free(arr);
    assert(lst->head != NULL);
    assert(lst->head->data == &data1);
    assert(lst->head->next->data == &data2);
    assert(lst->head->next->next == NULL);
    assert(lst->size == 2);

    lstdestroy(lst);
}


int main(void) {
    test01empty();
    test02add();
    test03remove_0();
    test03remove_1();  
    test03remove_2();
    test04size();
    test05getset();
    test06lsttoarr();
    test07arrtolst();

    return 0;
}
