#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* lista = (List *)malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return lista;
}

void * firstList(List * list) {
    if (list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list->current == NULL) return NULL;
    list->current = list->current->next;
    if(list->current == NULL) return NULL;
    return list->current->data;
}

void * lastList(List * list) {
    if (list->tail == NULL) return NULL;
    list->current = list->tail;
    while (list->current != NULL && list->current->next != NULL){
        list->current = list->current->next;
    }
    if(list->current == NULL) return NULL;
    return list->current->data;
}

void * prevList(List * list) {
    
    if (list->current == NULL) return NULL;
    if (list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* aux = createNode(data);
    if (list->head == NULL){
        list->head = aux;
        list->tail = list->head;
    } else {
        aux->next = list->head;
        list->head->prev = aux;
        list->head = aux;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node * new_node = createNode(data);
    new_node->prev = list->current; // current <- new
    new_node->next = list->current->next;   // current <- new -> next
    if (list->current->next != NULL){
        list->current->next->prev = new_node;  // current <- new <-> next
    } else {
        list->tail = new_node;  // current <- new
    }
    list->current->next = new_node; // current <-> new // current <-> new <-> next
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}