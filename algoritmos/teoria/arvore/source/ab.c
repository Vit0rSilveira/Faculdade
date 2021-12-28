#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ab.h"

struct no {
    no_t *esq;
    no_t *dir;
    elem info;
};


arvore_t *criar() {
    arvore_t *a = malloc(sizeof(arvore_t));

    a->raiz = NULL;

    return a;
}

int esta_vazia(arvore_t *a) {
    assert(a != NULL);

    if (a->raiz == NULL)
        return 1;

    return 0;
}

void finalizar(no_t *raiz) {
    if (raiz != NULL) {
        finalizar (raiz->esq);
        finalizar (raiz->dir);
        free(raiz);
    }
}

void imprimir(no_t *raiz) {
    if (raiz != NULL) {
        printf("%d(", raiz->info);
        imprimir(raiz->esq);
        printf(",");
        imprimir(raiz->dir);
        printf(")");
    }
    else {
        printf("null");
    }
}

int altura(no_t*raiz) {
    if (raiz == NULL)
        return 0;
    
    int altEsq = 1 + altura(raiz->esq);
    int altDir = 1 + altura(raiz->dir);

    if (altEsq > altDir)
        return altEsq;
    else
        return altDir;
}

no_t *busca(no_t *raiz, elem x) {
    if (raiz == NULL)
        return NULL;
    
    if (raiz->info == x)
        return raiz;
    
    no_t *p = busca(raiz->esq, x);
    if (p == NULL)
        p = busca(raiz->dir, x);

    return p;
}

no_t *busca_pai(no_t *raiz, elem x) {
    if (raiz == NULL)
        return NULL;
    
    if (raiz->esq != NULL && raiz->esq->info == x)
        return raiz;
    
    if (raiz->dir != NULL && raiz->dir->info == x)
        return raiz;
    
    no_t *p = busca_pai(raiz->esq, x);
    if (p == NULL)
        p = busca_pai(raiz->dir, x);

    return p;
}
// se pai = -1 --> inserir na raiz
// Caso contrario, insere esquerda do pai
int inserir_esq(arvore_t *a, elem x, elem pai) {
    no_t *p = malloc(sizeof(no_t));

    p->esq = NULL;
    p->dir = NULL;
    p->info = x;

    if (pai == -1) {
        if (a->raiz == NULL) {
            a->raiz = p;
        }
        else {
            free(p);
            return 0;
        }
    }
    else {
        no_t *aux = busca(a->raiz, pai);
        
        if (aux != NULL && aux->esq == NULL) {
            aux->esq = p;
        } else {
            return 0;
        }
    }

    return 1;

}

int inserir_dir(arvore_t *a, elem x, elem pai) {
    no_t *p = malloc(sizeof(no_t));

    p->esq = NULL;
    p->dir = NULL;
    p->info = x;

    if (pai == -1) {
        if (a->raiz == NULL) {
            a->raiz = p;
        }
        else {
            free(p);
            return 0;
        }
    }
    else {
        no_t *aux = busca(a->raiz, pai);
        
        if (aux != NULL && aux->dir == NULL) {
            aux->dir = p;
        } else {
            return 0;
        }
    }

    return 1;
}

int remover(arvore_t *a, elem x) {
    no_t *p, *pai;
    int ehEsq;

    // 1º Etapa: Setar p e pai
    if (a->raiz != NULL && a->raiz->info == x) {
        p = a->raiz;
        pai = NULL;
    }
    else {
        pai = busca_pai(a->raiz, x);
        if (pai != NULL) {
            if (pai->esq != NULL && pai->esq->info == x) {
                p = pai->esq;
                ehEsq = 1;
            }
            else {
                p = pai->dir;
                ehEsq = 0;
            }
        }
        else {
            p = NULL;
        }
    }

    //2 etapa: fazer a remoção de p;
    if (p == NULL)
        return 0;
    else {
        if (p->esq == NULL && p->dir == NULL) { // P é folha
            if (pai == NULL) {
                free(p);
                a->raiz = NULL;
            }
            else {
                if (ehEsq)
                    pai->esq = NULL;
                else
                    pai->dir = NULL;

                free(p);
            }
        }
        else {
            if (p->esq != NULL) {
                p->info = p->esq->info;
                p->esq->info = x;
            }
            else {
                p->info = p->dir->info;
                p->dir->info = x;
            }
            return remover(a, x);
        }
    }
    return 1;
}

void pre_ordem(no_t *raiz) {
    if (raiz == NULL)
        return;
    
    printf("%d ", raiz->info);
    pre_ordem(raiz->esq);
    pre_ordem(raiz->dir);
}

void em_ordem(no_t *raiz) {
    if (raiz == NULL)
    return;
    
    em_ordem(raiz->esq);
    printf("%d ", raiz->info);
    em_ordem(raiz->dir);
}

void pos_ordem(no_t *raiz) {
    if (raiz == NULL)
    return;
    
    pos_ordem(raiz->esq);
    pos_ordem(raiz->dir);
    printf("%d ", raiz->info);
}