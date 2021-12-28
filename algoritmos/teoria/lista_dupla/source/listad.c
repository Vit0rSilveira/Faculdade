#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "listad.h"

typedef struct no no_t;

struct no {
    elem info;
    no_t *ant;
    no_t *prox;
};

struct lista {
    no_t *ini;
    no_t *fim;
};

listad_t *criar() {
    listad_t *l = malloc(sizeof(listad_t));
    assert(l != NULL);

    l->ini = NULL;
    l->fim = NULL;

    return l;
}

void liberar(listad_t *l) {
    if(l != NULL) {
        no_t *aux = l->ini;
        while(aux != NULL) {
            l->ini = l->ini->prox;
            free(aux);
            aux = l->ini;
        }
        free(l);
    }
}

int inserir(listad_t *l, elem x) {
    assert(l != NULL);

    no_t *p = malloc(sizeof(no_t));

    p->info = x;
    p->prox = NULL;
    p->ant = NULL;

    no_t *aux = l->ini;
    no_t *ant = NULL;
    
    while(aux != NULL && x > aux->info) {
        ant = aux;
        aux = aux->prox;
    }

    // Caso onde x já existe na lista.
    if(aux != NULL && x == aux->info){
        free(p);
        return 0;
    }
    
    // Inserindo no inicio, lista vazia ou lista com elementos.
    if(ant == NULL) {
        p->prox = l->ini;
        if(l->ini != NULL)
            l->ini->ant = p;
        l->ini = p;
    }
    //Inserção no meio ou no fim da lista.
    else {
        p->prox = ant->prox;
        ant->prox = p;
        if(p->prox != NULL)
            p->prox->ant = p;
        else
            l->fim = p;
        p->ant = ant;
    }

    return 1;
}

int remover(listad_t *l, elem x) {
    assert(l != NULL);

    no_t *p = l->ini;
    no_t *ant = NULL;

    while(p != NULL && x > p->info) {
        ant = p;
        p = p->prox;
    }

    if(p == NULL)
        return 0;

    // Remoção do primeiro elemento.
    if(ant == NULL) {
        l->ini = l->ini->prox;
        if(l->ini != NULL)
            l->ini->ant = NULL;
        else
            l->fim = NULL;
        free(p);
    }
    // Remoção de elemento no meio ou no fim.
    else {
        // Remover no fim.
        if(p->prox == NULL) {
            l->fim = p->ant;
            ant->prox = NULL;
            free(p);
        }
        else {
            ant->prox = p->prox;
            p->prox->ant = ant;
            free(p);
        }
    }

    return 1;
}

void imprimir(listad_t *l) {
    assert(l != NULL);
    no_t *p = l->ini;

    while(p != NULL) {
        printf("%d ", p->info);
        p = p->prox;
    }
    printf("\n");
}

void imprimir_inv(listad_t *l) {
    assert(l != NULL);
    no_t *p = l->fim;

    while(p != NULL) {
        printf("%d ", p->info);
        p = p->ant;
    }
    printf("\n");
}