#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "skiplist.h"


typedef struct no no_t;

struct no {
    void *item;
    no_t **prox;
};

struct skiplist {
    int nivelMax;
    int nivelUsado;
    no_t *ini;
};

/**
 * @brief Verifica a alocação feita pelo algoritmo.
 * 
 * @param x 
 * @return int 
 */
static int verifica_alocacao(int x) {
    if (!x)
        return 0;
    
    return 1;
}

/**
 * @brief Cria um novo nó usado pela skiplist, esse nó possui um elemento
 * e um nível, o nível é o tamanho do vetor de ponteiros que este elemento terá.
 * No momento de alocar, é alocado nível + 1, pois na linguagem c, os indices
 * começam em zero.
 * 
 * @param elem Item no qual o nó terá
 * @param nivel Valor do nível que o nó criado terá.
 * @return no_t* Retorna o nó criado.
 */
static no_t *novo_no(void *elem, int nivel) {
    no_t *no = malloc(sizeof(no_t));
    if (!verifica_alocacao(no != NULL)) {
        printf("Problema ao criar um no\n");
        return NULL;
    }
    no->item = elem;
    no->prox = malloc((nivel + 1) * sizeof(no_t *));

    for (int i = 0; i < nivel + 1; i++)
        no->prox[i] = NULL;

    return no;
}

/**
 * @brief Calcula o nível que o nó adicionado na skiplist terá
 * 
 * @return int Retona o valor do nó resto da divisão pelo nível máximo, para
 * garantir que o nível não passará do nível máximo.
 */
static int calcular_nivel() {
    int qtd = 0;

    while (rand() % 2 == 0) {
        qtd++;
    }

    return qtd % (NIVEL_MAX + 1);
}

dicionario_t *criar() {
    dicionario_t *sk = malloc(sizeof(dicionario_t));
    if (!verifica_alocacao(sk != NULL)) {
        printf("Problema ao criar uma SkipList\n");
        return NULL;
    }

    sk->nivelMax = NIVEL_MAX;
    sk->nivelUsado = 0;

    sk->ini = novo_no(NULL, NIVEL_MAX);

    return sk;
}

int inserir (dicionario_t *sk, void *elem, comparar_t *comparar) {
    if (!verifica_alocacao(sk != NULL))
        return 0;
    
    no_t *noAtual = sk->ini;
    /*  Este auxiliar salva os pontos por onde o no atual passou durante o
        o percurso, para que assim, possa ser feita a ligação dos anteriores com
        o nó da frente */
    no_t **aux = malloc((NIVEL_MAX + 1) * sizeof(no_t *));

    for (int i = sk->nivelUsado; i >= 0; i--) {
        while (noAtual->prox[i] != NULL && comparar(noAtual->prox[i]->item, elem) < 0)
            noAtual = noAtual->prox[i];

        aux[i] = noAtual;
    }
    noAtual = noAtual->prox[0];

    if (noAtual != NULL && comparar(noAtual->item, elem) == 0) {
        free(aux);
        return 0;
    }

    int qtdNivel = calcular_nivel();

    no_t *no = novo_no(elem, qtdNivel);

    if (qtdNivel > sk->nivelUsado) {
        for (int i = sk->nivelUsado + 1; i <= qtdNivel; i++)
            aux[i] = sk->ini;
        
        sk->nivelUsado = qtdNivel;
    }

    for (int i = 0; i <= qtdNivel; i++) {
        no->prox[i] = aux[i]->prox[i];
        aux[i]->prox[i] = no;
    }

    free(aux);

    return 1;
}

int remover (dicionario_t *sk, char *elem, comparar_t *comparar, free_t *free_fun) {
    if (!verifica_alocacao(sk != NULL))
        return 0;
    
    no_t *noAtual = sk->ini;
    no_t **aux = malloc((NIVEL_MAX + 1) * sizeof(no_t *));

    for (int i = sk->nivelUsado; i >= 0; i--) {
        while (noAtual->prox[i] != NULL && comparar(noAtual->prox[i]->item, elem) < 0)
            noAtual = noAtual->prox[i];

        aux[i] = noAtual;
    }
    noAtual = noAtual->prox[0];

    if (noAtual == NULL || comparar(noAtual->item, elem) != 0) {
        free(aux);
        return 0;
    }

    for (int i = 0; i <= sk->nivelUsado && aux[i]->prox[i] == noAtual; i++)
        aux[i]->prox[i] = noAtual->prox[i];

    while (sk->ini->prox[sk->nivelUsado] == NULL && sk->nivelUsado > 0)
        sk->nivelUsado--;

    free_fun(noAtual->item);
    free(noAtual->prox);
    free(noAtual);
    free(aux);

    return 1;
}

int alterar (dicionario_t *sk, void *elem, comparar_t *comparar, free_t *free_fun) {
    if (!verifica_alocacao(sk != NULL))
        return 0;

    no_t *noAtual = sk->ini;

    for (int i = sk->nivelUsado; i >= 0; i--) {
        while (noAtual->prox[i] != NULL && comparar(noAtual->prox[i]->item, elem) < 0)
            noAtual = noAtual->prox[i];
    }
    noAtual = noAtual->prox[0];

    if (noAtual != NULL && comparar(noAtual->item, elem) == 0) {
        void *aux = noAtual->item;

        noAtual->item = elem;

        free_fun(aux);

        return 1;
    }

    return 0;
}

int imprimir (dicionario_t *sk, char *c, comparar_t *comparar, imprimir_t *imprimir){
    if (!verifica_alocacao(sk != NULL))
        return 0;
    
    no_t *noAtual = sk->ini;

    for (int i = sk->nivelUsado; i >= 0; i--) {
        while (noAtual->prox[i] != NULL && comparar(noAtual->prox[i]->item, c) < 0) {
            noAtual = noAtual->prox[i];
        }
    }
    noAtual = noAtual->prox[0];

    if (noAtual == NULL || comparar(noAtual->item, c) != 0)
        return 0;
    
    while (noAtual != NULL && comparar(noAtual->item, c) == 0) {
        imprimir(noAtual->item);
        noAtual = noAtual->prox[0];
    }

    return 1;
}

int buscar (dicionario_t *sk, char *c, comparar_t *comparar, imprimir_t *imprimir) {
    if (!verifica_alocacao(sk != NULL))
        return 0;
    
    no_t *noAtual = sk->ini;

    for (int i = sk->nivelUsado; i >= 0; i--) {
        while (noAtual->prox[i] != NULL && comparar(noAtual->prox[i]->item, c) < 0) {
            noAtual = noAtual->prox[i];
        }
    }
    
    noAtual = noAtual->prox[0];
    if (noAtual != NULL && comparar(noAtual->item, c) == 0) {
        imprimir(noAtual->item);
        return 1;
    }

    return 0;
}

void destruir (dicionario_t *sk, free_t *free_fun) {
    if (!verifica_alocacao(sk != NULL))
        return;

    no_t *noAtual = sk->ini;

    while (noAtual != NULL) {
        no_t *aux = noAtual;
        noAtual = noAtual->prox[0];
        
        if (aux->item != NULL)
            free_fun(aux->item);

        free(aux->prox);
        free(aux);
    }
    free(sk);
}