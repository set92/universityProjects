#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "definitions.h"

extern object3d *_selected_object;

//this link always point to first Link 
struct typeNode *head = NULL;

//this link always point to last Link 
struct typeNode *last = NULL;

struct typeNode *current = NULL;

//is list empty
bool isEmpty() {
    return head == NULL;
}

int length() {
    int length = 0;
    struct typeNode *current;

    for (current = head; current != NULL; current = current->next) length++;

    return length;
}

//display the list in from first to last
void displayForward() {

    //start from the beginning
    struct typeNode *ptr = head;

    //navigate till the end of the list
    printf("\n[ ");

    for (int i = 0; ptr != NULL; ++i) {
        printf("(%.2f\n) ", ptr->m[i]);
        ptr = ptr->next;
    }

    printf(" ]");
}

//insert link at the first location
void insertFirst(typeNode *v) {
    v->next = _selected_object->pila;
    if (_selected_object->pila == NULL) _selected_object->pila->prev = v;
    _selected_object->pila = v;
}

//delete first item
struct typeNode *deleteFirst() {

    //save reference to first link
    struct typeNode *tempLink = head;

    //if only one link
    if (head->next == NULL) {
        last = NULL;
    } else {
        head->next->prev = NULL;
    }

    head = head->next;
    //return the deleted link
    return tempLink;
}
