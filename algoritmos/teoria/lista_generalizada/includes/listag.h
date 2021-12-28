#ifndef LISTAG_H
#define LISTAG_H


enum tipos {ATOMO, SUBLISTA};

typedef int elem;

typedef struct no no_t;

typedef union {
    elem atomo;
    no_t *sublista;
} info_t;

struct no {
    int tipo;
    info_t info;
    no_t *prox;
};


void liberar(no_t *p);
no_t *atomo(elem x);
no_t *sublista(no_t *sublista);
no_t *concat(no_t *p, no_t *q);
info_t cabeca(no_t *p, int *tipo);
no_t *cauda(no_t *p);
void imprimir(no_t *p);


#endif