#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "listag.h"


void liberar(no_t *p) {
    assert(p != NULL);

    no_t *aux;

    while(p != NULL) {
        if(p->tipo == SUBLISTA)
            liberar(p->info.sublista);

        aux = p;
        p = p->prox;
        free(aux);
    }
}

no_t *atomo(elem x) {
    no_t *p = malloc(sizeof(no_t));
    assert(p != NULL);

    p->tipo = ATOMO;
    p->prox = NULL;
    p->info.atomo = x;

    return p;
}

no_t *sublista(no_t *sublista) {
    no_t *p = malloc(sizeof(no_t));
    assert(p != NULL);

    p->tipo = SUBLISTA;
    p->prox = NULL;
    p->info.sublista = sublista;

    return p;
}

no_t *concat(no_t *p, no_t *q) {
    assert(p != NULL);

    p->prox = q;

    return p;
}

info_t cabeca(no_t *p, int *tipo) {
    assert(p != NULL);

    *tipo = p->tipo;
    return p->info;

}

no_t *cauda(no_t *p) {
    assert(p != NULL);

    return p->prox;
}

void imprime(no_t *p) {
    if(p == NULL)
        return;
    printf("(");

    while(p != NULL) {
        if(p->tipo == ATOMO)
            printf("%d", p->info.atomo);
        else
            imprime(p->info.sublista);

        if(p->prox != NULL)
            printf(",");

        p = p->prox;
    }
    printf(")");
}

void imprimir(no_t *p) {
    imprime(p);
    printf("\n");
}