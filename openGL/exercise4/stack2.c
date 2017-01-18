#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "definitions.h"

extern object3d *_selected_object;

//this link always point to last Link
struct typeNode *current = NULL;

//is list empty
bool isEmpty() {
    return _selected_object->pila == NULL;
}

int length() {
    int length = 0;
    struct typeNode *current;

    for (current = _selected_object->pila; current != NULL; current = current->next) length++;

    return length;
}

//insert link at the first location
void insertFirst(typeNode *v) {
    typeNode *aux;
    //free los demás nodos
    while (_selected_object->pila->prev != NULL) {
        aux = _selected_object->pila->prev;
        _selected_object->pila->prev = _selected_object->pila->prev->prev;
        free(aux);
    }

    // código de añadir
    v->next = NULL;
    v->prev = NULL;

    if (_selected_object->pila == NULL) _selected_object->pila = v;
    else {
        v->next = _selected_object->pila;
        v->next->prev = v;
        _selected_object->pila = v;
    }
}

void deleteFirst() {
    if (_selected_object->pila->next != NULL) _selected_object->pila = _selected_object->pila->next;

}

void deleteMiddle() {
    if (_selected_object->pila->prev != NULL) _selected_object->pila = _selected_object->pila->prev;

}