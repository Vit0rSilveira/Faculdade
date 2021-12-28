#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct no no_t;

struct no {
    elem info;
    no_t *prox;
};

struct lista {
    no_t *ini;
    no_t *fim;
    int tam; 
};

lista_t *criar() {
    lista_t *l = (lista_t *)malloc(sizeof(lista_t));
    assert(l != NULL);

    l->ini = NULL;
    l->fim = NULL;
    l->tam = 0;

    return l;
}

void liberar(lista_t *l) {
    if (l != NULL) {
        no_t *p = l->ini;

        while (p != NULL) {
            l->ini = p->prox;
            free(p);
            p = l->ini;
        }
        free(l);
    }
}

void inserir(lista_t *l, elem x) {
    assert(l != NULL);

    if(esta_na_lista(l,x)) //impoe que só armazene elementos distintos.
        return;

    no_t *p = malloc(sizeof(no_t));
    p->info = x;
    p->prox = NULL;

    //1º Caso: Lista vazia.
    if (l->ini == NULL) {
        l->ini = p;
        l->fim = p;
    }
    else
        l->fim->prox = p;

    l->fim = p;
    l->tam ++;
}

int tamanho(lista_t *l) {
    assert(l != NULL);

    return l->tam;
}

void imprimir (lista_t *l) {
    assert(l != NULL);

    no_t *p = l->ini;
    while(p != NULL) {
        printf("%d ", p->info);
        p = p->prox;
    }
    printf("\n");
}

int esta_na_lista(lista_t *l, elem x) {
    assert(l != NULL);

    no_t *p = l->ini;

    while(p != NULL) {
        if(p->info == x)
            return 1;
        
        p = p->prox;
    }

    return 0;
}

int remover(lista_t *l, elem x) {
    assert(l != NULL);

    no_t *p = l->ini;
    no_t *antes = NULL;

    while(p != NULL) {
        if(p->info == x) {
            // 1º Caso: Remover do inicio
            if(p == l->ini) { // Ou  antes == NULL
                l->ini = l->ini->prox;
                free(p);
            }
            else if(p == l->fim) {
                l->fim = antes;
                l->fim->prox = NULL;
                free(p);
            }
            else { // Remover do meio
                antes->prox = p->prox;
                free(p);
            }
            l->tam--;
            return 1;
        }
        else {
        antes = p;
        p = p->prox;
        }

    }

    return 0;
}