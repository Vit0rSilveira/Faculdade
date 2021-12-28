#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treap.h"
#include "fila.h"


struct no {
    no_t *esq;
    no_t *dir;
    int info;
    int prior;
};

struct arvore {
    no_t *raiz;
};



arvore_t *criar_treap() {
    arvore_t *a = malloc(sizeof(arvore_t));

    a->raiz = NULL;

    return a;
}

static void liberar_treap(no_t *raiz) {
    if (raiz == NULL) return;

    liberar_treap(raiz->esq);
    liberar_treap(raiz->dir);
    free(raiz);
}

void deletar_treap (arvore_t *a) {
    if (a == NULL) return ;

    liberar_treap(a->raiz);
    free(a);
}

/**
 * @brief Faz rotação para esquerda em um nó desbalanceado.
 * 
 * @param desb 
 * @return no_t* 
 */
static no_t *rotacao_EE(no_t *desb) {
    no_t *aux = desb->dir;
    desb->dir = aux->esq;
    aux->esq = desb;

    return aux;
}

/**
 * @brief Faz a rotação para direita em um nó desbalanceado.
 * 
 * @param desb 
 * @return no_t* 
 */
static no_t *rotacao_DD(no_t *desb) {
    no_t *aux = desb->esq;
    desb->esq = aux->dir;
    aux->dir = desb;

    return aux;
}

/**
 *  @brief Função recursiva na qual procura o lugar de inserção na árvore
 * respeitando a defição de árvore binária de busca, e após a inserção verifica
 * se necessita rotacionar os nos para manter o estado de "Heap".
 * 
 * @param raiz É necessário ser ponteiro de ponteiro, pois o ponteiro raiz será
 * alterado na função.
 * @param info 
 * @param prior 
 */
static void inserir_no(no_t **raiz, int info, int prior) {
    // Se encontrei um nó nulo, é aqui que eu devo inserir.
    if (*raiz == NULL) {
        *raiz = malloc(sizeof(no_t));

        (*raiz)->info = info;
        (*raiz)->prior = prior;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
    }
    /*  Se o valor for menor que o valor do nó, insiro a esquerda e verifico
        o estado de Heap */
    else if ((*raiz)->info > info) {
        inserir_no(&(*raiz)->esq, info, prior);

        if ((*raiz)->prior < (*raiz)->esq->prior)
            (*raiz) = rotacao_DD((*raiz));
    }
    /*  Se o valor for maior que o valor do nó, insiro a esquerda e verifico
        o estado de Heap */
    else {
        inserir_no(&(*raiz)->dir, info, prior);

        if ((*raiz)->prior < (*raiz)->dir->prior)
            (*raiz) = rotacao_EE((*raiz));
    }
}

int inserir_treap(arvore_t *a, int info, int prior) {
    if (a == NULL) return -1;

    // Se o elemento existe na Treap, não adiciona - se
    if (buscar_treap(a, info)) return 0;
    
    inserir_no(&a->raiz, info, prior);

    return 1;
}

/**
 * @brief Função recursiva que remove o nó da árvore
 * 
 * @param raiz 
 * @param info 
 * @return int 
 */
static void remover_no(no_t **raiz, int info) {
    if (*raiz == NULL) 
        return;
    else if ((*raiz)->info > info)
        remover_no(&(*raiz)->esq, info);
    else if ((*raiz)->info < info)
        remover_no(&(*raiz)->dir, info);
    // Caso seja um nó folha.
    else if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
        free((*raiz));
        *raiz = NULL;
        return;
    }
    // Caso exista apenas um filho a direita
    else if ((*raiz)->esq == NULL) {
        no_t *aux = *raiz;
        *raiz = (*raiz)->dir;
        free(aux);
    }
    // Caso exista um filho a esquerda.
    else if ((*raiz)->dir == NULL) {
        no_t *aux = *raiz;
        *raiz = (*raiz)->esq;
        free(aux);
    }
    /*	Caso tenha os dois filhos. Rotaciono com o nó da esquerda e removo
        a esquerda, basicamene eu rotaciono e faço cair no caso de ter
        1 filho só. */
    else {
        (*raiz) = rotacao_EE((*raiz));
        remover_no(&(*raiz)->esq, info);
    }

}

int remover_treap(arvore_t *a, int info) {
    if (a == NULL) return -1;

    if (!buscar_treap(a, info)) return 0;
    remover_no(&a->raiz, info);

    return 1; 
}

static int buscar(no_t *raiz, int info) {
    // Se pecorri até chegar em nó nulo é porque não existe.
    if (raiz == NULL) 
        return 0;
    // Existe.
    else if (raiz->info == info) 
        return 1;
    // Procurar nos filhos a esquerda
    else if (raiz->info > info)
        return buscar(raiz->esq, info);
    // Procurar nos filhos a direita
    else
        return buscar(raiz->dir, info);

    return 0;
}

int buscar_treap(arvore_t *a, int info) {
    if (a == NULL) return 0;

    return buscar(a->raiz, info);
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

void imprimir_treap(arvore_t *a) {
    if (a == NULL) return;

    imprimir(a->raiz);
    printf("\n");
}

/**
 * @brief Visita - se a raiz, a subárvore da esquerda e a subárvore da direita
 * respectivamente
 * 
 * @param a 
 */
static void pre_ordem(no_t *raiz) {
    if (raiz == NULL) return;

    printf("(%d, %d) ", raiz->info, raiz->prior);
    pre_ordem(raiz->esq);
    pre_ordem(raiz->dir);

}

void impressao_pre_ordem(arvore_t *a) {
    if (a == NULL) return;

    pre_ordem(a->raiz);
    printf("\n");
}

/**
 * @brief Visita - se subárvore da esquerda, raiz e a subárvore da direita
 * respectivamente.
 * 
 * @param raiz 
 */
static void em_ordem(no_t *raiz) {
    if (raiz == NULL) return;

    em_ordem(raiz->esq);
    printf("(%d, %d) ", raiz->info, raiz->prior);
    em_ordem(raiz->dir);
}

void impressao_em_ordem(arvore_t *a) {
    if (a == NULL) return;

    em_ordem(a->raiz);
    printf("\n");
}

/**
 * @brief Visita - se subárvore da esquerda, subárvore da direita e raiz
 * respectivamente
 * 
 * @param raiz 
 */
static void pos_ordem(no_t *raiz) {
    if (raiz == NULL) return;

    pos_ordem(raiz->esq);
    pos_ordem(raiz->dir);
    printf("(%d, %d) ", raiz->info, raiz->prior);
}

void impressao_pos_ordem(arvore_t *a) {
    if (a == NULL) return;

    pos_ordem(a->raiz);
    printf("\n");
}

void impressao_em_largura(arvore_t *a) {
    // Crio uma fila que funcionára como um auxiliar para printar em largura.
    fila_t *f = criar_fila();
    // Insiro a raiz da árvore na lista.
    inserir_fila(f, a->raiz);

    while (!esta_vazia(f)) {
        no_t *aux = (no_t *)remover_fila(f);

        printf("(%d, %d) ", aux->info, aux->prior);

        if (aux->esq != NULL)
            inserir_fila(f, aux->esq);
        if (aux->dir != NULL)
            inserir_fila(f, aux->dir);
    }
    printf("\n");

    deletar_fila(f);
    
}