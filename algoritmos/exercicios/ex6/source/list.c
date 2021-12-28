#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct node node_t;

static void my_assert(int teste) {
    if(teste == 0)
        exit(0);
}

struct node {
    elem info;
    node_t *prox;
};

struct list {
    node_t *ini;
    node_t *end;
    int size;
};

list_t *creat_list() {
    list_t *l = malloc(sizeof(list_t));
    my_assert(l != NULL);

    l->ini = NULL;
    l->end = NULL;
    l->size = 0;

    return l;
}

void push(list_t *l, elem x) {
    node_t *n = malloc(sizeof(node_t));
    my_assert(n != NULL);

    n->info = x;
    n->prox = NULL;

    if(l->ini == NULL) {
        l->ini = n;
        l->end = n;
    }
    else
        l->end->prox = n;
    
    l->end = n;
    l->size++;
}

void print_list(list_t *l) {
    node_t *n = l->ini;

    while(n != NULL) {
        printf("%d ", n->info);
        n = n->prox;
    }
    printf("\n");
}

void delete_list(list_t *l) {
    if (l != NULL) {
        node_t *n = l->ini;

        while(n != NULL) {
            l->ini = n->prox;
            free(n);
            n = l->ini;
        }
        free(l);
    }
}

void rotate_list(list_t *l, int rotation) {
    my_assert(l != NULL);

    for(int i = 0; i < rotation; i++) {
        node_t *n = l->ini;

        l->end->prox = l->ini;
        l->ini = l->end;

        while(n->prox != l->end)
            n = n->prox;

        n->prox = NULL;
        l->end = n;
    }
}