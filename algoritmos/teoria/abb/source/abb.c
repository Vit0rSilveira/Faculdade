#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "abb.h"

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
    if (!raiz) return NULL;
    else if (raiz->info == x) return raiz;
    else if (x < raiz->info) return busca(raiz->esq, x);
    else return busca(raiz->dir, x);
}

int inserir(no_t **raiz, elem x) {
    if (*raiz == NULL) {
        *raiz = malloc(sizeof(no_t));
        (*raiz)->info = x;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;

        return 1;
    }
    else if (x == (*raiz)->info)
        return 0;
    else if (x < (*raiz)->info)
        return inserir(&(*raiz)->esq, x);
    else
        return inserir(&(*raiz)->dir, x);
}

int remover(no_t **raiz, elem x) {
    if (*raiz == NULL) 
        return 0;
    else if (x < (*raiz)->info)
        return remover(&(*raiz)->esq, x); 
    else if (x > (*raiz)->info)
        return remover(&(*raiz)->dir, x);
    else {
        // Remoção de Folhas
        if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
            free(*raiz);
            *raiz = NULL;
            return 1;
        } // caso tenha um filho só na direira
        else if ((*raiz)->esq == NULL) {
            no_t *aux = *raiz;
            *raiz = (*raiz)->dir;
            free(aux);
            return 1;
        } // caso tenha um filho só na esquerda
        else if ((*raiz)->dir == NULL) {
            no_t *aux = *raiz;
            *raiz = (*raiz)->esq;
            free(aux);
            return 1;
        }
         /*	Caso tenha os dois filhos. Pegar o maior do lado esquerdo, ou o menor do lado direito
         	e mover para o lugar do elemento que eu estou buscando remover. */
        else {
            // Nesta caso vou pegar o maior do lado esquerdo.
            no_t *aux = (*raiz)->esq;

            // Percorro até chegar no maior elemento.
            while (aux->dir != NULL)
                aux = aux->dir;
            
            // Minha raiz que eu quero remover, recebe o novo valor.
            (*raiz)->info = aux->info;

            /*  Chamo recursivamente para a parte esquerda, a partir do nó eu 
                troquei o valor, passando o valor do elemento que eu mandei pro
                nó. Assim, a remoção é feita. */
            return remover(&(*raiz)->esq, aux->info);
            return 1;
        }
    }
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
