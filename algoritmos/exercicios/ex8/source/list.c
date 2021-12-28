#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct no no_t;


struct no {
    elem info;
    no_t *prox;
};

struct list {
    no_t *begin;
    no_t *end;
    int size;
};

static void my_assert(int test) {
    if (!test)
        exit(EXIT_FAILURE);
}

list_t *creat_list() {
    list_t *l = malloc(sizeof(list_t));
    my_assert(l != NULL);

    l->begin = NULL;
    l->end = NULL;
    l->size = 0;

    return l;
}

void push_list(list_t *l, elem x) {
    my_assert(l != NULL);

    no_t *node = malloc(sizeof(no_t));
    my_assert(node != NULL);

    node->info = x;
    node->prox = NULL;

    if (l->begin == NULL) {
        l->begin = node;
        l->end = node;
    }
    else {
        l->end->prox = node;
    }

    l->end = node;
    l->size++;

}

void remove_elem_list(list_t *l, elem x) {
    my_assert(l != NULL);

    no_t *aux = l->begin;
    no_t *ant = NULL;

    while (aux != NULL) {
        if (aux->info == x) {
            if (aux == l->begin) {
                l->begin = l->begin->prox;
                free(aux);
            }
            else if (aux == l->end) {
                l->end = ant;
                l->end->prox = NULL;
                free(aux);
            }
            else {
                ant->prox = aux->prox;
                free(aux);
            }
            l->size--;
            return;
        }
        else {
            ant = aux;
            aux = aux->prox;
        }
    }
}

void free_list(list_t *l) {
    my_assert(l != NULL);

    no_t *aux = l->begin;

    while (aux != NULL) {
        l->begin = aux->prox;
        free(aux);
        aux = l->begin;
    }
    free(l);

}

int size_list(list_t *l) {
    my_assert(l != NULL);

    return l->size;
}

void access_elements(list_t *l1, list_t *l2, void (*func)(elem*, elem*)) {
    my_assert(l1 != NULL && l2 != NULL);

    no_t *aux1 = l1->begin;
    no_t *aux2 = l2->begin;

    while (aux1 != NULL && aux2 != NULL) {
        func(&aux1->info, &aux2->info);
        
        aux1 = aux1->prox;
        aux2 = aux2->prox;
    }
}

void show_list(list_t *l, void (*show_elem)(elem, int, int)) {
    my_assert(l != NULL);

    no_t *aux = l->begin;

    while (aux != NULL) {
        show_elem(aux->info, (aux == l->begin), (aux == l->end));
        aux = aux->prox;
    }
}