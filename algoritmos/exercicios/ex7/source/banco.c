#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"

typedef struct no no_t;

struct no {
    int code;
    char *name;
    no_t *prox;
    no_t *ant;
};

struct banco {
    no_t *begin;
    no_t *end;
};

static void check_null(int test) {
    if(!test)
        exit(EXIT_FAILURE);
}

static void delete_no(no_t *node) {
    free(node->name);
    free(node);
}

banco_t *creat() {
    banco_t *b = malloc(sizeof(banco_t));
    check_null(b != NULL);

    b->begin = NULL;
    b->end = NULL;

    return b;
}

int is_empty(banco_t *b) {
    check_null(b != NULL);

    if(b->begin == NULL)
        return 1;
    
    return 0;
}

void insert(banco_t *b, int code, char *name) {
    check_null(b != NULL);

    no_t *n = malloc(sizeof(no_t));
    n->code = code;
    n->name = name;
    n->ant = NULL;
    n->prox = NULL;

    no_t *aux = b->begin;
    no_t *ant = NULL;
    while(aux != NULL && code > aux->code) {
        ant = aux;
        aux = aux->prox;
    }

    // Caso onde x já existe na lista.
    if(aux != NULL && code == aux->code){
        printf("INVALIDO\n");
        free(name);
        free(n);
        return;
    }

    // Lista vazia ou inserir no início
    if(ant == NULL) {
        n->prox = b->begin;

        //Verificar se a lista não está vazia
        if(b->begin != NULL)
            b->begin->ant = n;

        b->begin = n;
    } else {
        n->prox = ant->prox;
        ant->prox = n;

        //Verificar se está inserindo no meio da lista.
        if(aux != NULL)
            n->prox->ant = n;
        else
            b->end = n;

        n->ant = ant;
    }
}

void remove_elem(banco_t *b, int code) {
    check_null(b != NULL);

    no_t *aux = b->begin;
    no_t *ant = NULL;

    while(aux != NULL && code > aux->code) {
        ant = aux;
        aux = aux->prox;
    }

    if(aux == NULL) {
        printf("INVALIDO\n");
        return;
    }
    
    if(aux->code != code) {
        printf("INVALIDO\n");
        return;
    }

    if(ant == NULL) {
        b->begin = b->begin->prox;

        if(b->begin != NULL)
            b->begin->ant = NULL;
        else
            b->end = NULL;
        
        delete_no(aux);
    } else {
        if(aux->prox == NULL) {
            b->end = aux->ant;
            ant->prox = NULL;

            delete_no(aux);
        } else {
            ant->prox = aux->prox;
            ant->prox->ant = ant;

            delete_no(aux);
        }
    }
}

void imprimir(banco_t *b) {
    check_null(b != NULL);
    no_t *aux = b->begin;

    if(aux == NULL) {
        printf("VAZIA\n");
        return;
    }

    while(aux != NULL) {
        printf("%d, %s; ", aux->code, aux->name);
        aux = aux->prox;
    }
    printf("\n");
}

void free_bank(banco_t *b) {
    if (b != NULL) {
        no_t *tmp = b->begin;

        while (tmp != NULL) {
            b->begin = b->begin->prox;
            delete_no(tmp);
            tmp = b->begin;
        }
        free(b);
    }
}