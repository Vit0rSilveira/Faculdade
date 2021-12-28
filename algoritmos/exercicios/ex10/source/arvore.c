#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

struct no {
    int valor;
    int id;
    int idEsq;
    int idDir;
    no_t *esq;
    no_t *dir;
};

void inserir_no(no_t **raiz, int id, int valor, int idEsq, int idDir) {
    //  Se o nó é nulo, adiciono nele.
    if (*raiz == NULL) {
        *raiz = malloc(sizeof(no_t));

        (*raiz)->id = id;
        (*raiz)->valor = valor;
        (*raiz)->idEsq = idEsq;
        (*raiz)->idDir = idDir;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
        
        return;
    } 
    //  Se o id para eu adicionar é o do esquerdo, adiciono no esquerdo.
    else if (id == (*raiz)->idEsq)
        return inserir_no(&(*raiz)->esq, id, valor, idEsq, idDir);
    //  Se o id para eu adicionar é o do direito, adiciono no direito
    else if (id == (*raiz)->idDir)
        return inserir_no(&(*raiz)->dir, id, valor, idEsq, idDir);
    /*  Se o id não é nem o da esquerda e nem o da direita, preciso percorrer, 
        os outros nós se eles existem para verificar os ids dos filhos desses 
        nós e adicionar no lugar certo.*/
    else {
        if ((*raiz)->esq != NULL)
            inserir_no(&(*raiz)->esq, id, valor, idEsq, idDir);
        if ((*raiz)->dir != NULL)
            inserir_no(&(*raiz)->dir, id, valor, idEsq, idDir);
    }
}

arvore_t *criar() {
    arvore_t *a = malloc(sizeof(arvore_t));

    a->raiz = NULL;

    return a;
}

int esta_vazia(arvore_t *a) {
    if (!a) return 0;

    if (a->raiz == NULL)
        return 1;

    return 0;
}

void finalizar(no_t *raiz) {
    if (!raiz) return;

    finalizar(raiz->esq);
    finalizar(raiz->dir);
    free(raiz);
}

void imprimir(no_t *raiz) {
    if (raiz != NULL) {
        printf("%d(", raiz->valor);
        imprimir(raiz->esq);

        printf(",");

        imprimir(raiz->dir);
        printf(")");
    }
    else
        printf("null");

}

int altura(no_t*raiz) {
    if (!raiz) return 0;

    int altEsq = 1 + altura(raiz->esq);
    int altDir = 1 + altura(raiz->dir);

    if (altEsq > altDir)
        return altEsq;
    
    return altDir;
}

void soma_nos_filhos(const no_t *raiz, int *i) {
    // Se o nó não existe, eu retorno.
    if (!raiz) return;
    //  Se o nó for uma folha eu retorno.
    if (!raiz->esq &&  !raiz->dir) return;
    /*  Se Eu não tenho um nó e o outro existe e seu valor é o valor do pai
        chamo recursivamente para o nó existente */
    else if (!raiz->dir && raiz->esq && raiz->esq->valor == raiz->valor)
        soma_nos_filhos(raiz->esq, i);
    else if (!raiz->esq && raiz->dir && raiz->dir->valor == raiz->valor)
        soma_nos_filhos(raiz->esq, i);
    /*  Se o valor da soma dos filhos é p valor do pai, eu vou chamar
        recursivamente para cada filho, se os filhos existirem. */
    else if (raiz->esq->valor + raiz->dir->valor == raiz->valor) {
        soma_nos_filhos(raiz->esq, i);
        soma_nos_filhos(raiz->dir, i);
    } 
    // Se cheguei até aqui, é pq a soma dos filhos não e igual a do pai.
    else {
        *i = 0;
        return;
    }
}