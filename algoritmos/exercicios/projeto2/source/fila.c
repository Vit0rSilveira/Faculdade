#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct noFila noFila_t;

struct noFila {
    void *info;
    noFila_t *prox;
};

struct fila {
    noFila_t *ini;
    noFila_t *fim;
};

fila_t *criar_fila() {
    fila_t *l = (fila_t *)malloc(sizeof(fila_t));

    l->ini = NULL;
    l->fim = NULL;
    return l;
}

void deletar_fila(fila_t *l) {
    if (l != NULL) {
        noFila_t *p = l->ini;

        while (p != NULL) {
            l->ini = p->prox;
            free(p);
            p = l->ini;
        }
        free(l);
    }
}

void inserir_fila(fila_t *l, void *info) {
    noFila_t *p = malloc(sizeof(noFila_t));

    p->info = info;
    p->prox = NULL;

    //1º Caso: fila vazia.
    if (l->ini == NULL) {
        l->ini = p;
        l->fim = p;
    }
    else
        l->fim->prox = p;

    l->fim = p;
}

int esta_vazia(fila_t *l) {
    if (l == NULL) return 0;

    if (l->ini == NULL) return 1;

    return 0;
}

void *remover_fila(fila_t *l) {
    noFila_t *p = l->ini;

    if (p != NULL) {
        if (l->fim == l->ini)
            l->fim = NULL;

        l->ini = l->ini->prox;

        void *aux = p->info;
        free(p);
        
        return aux;
    }

    return NULL;
}