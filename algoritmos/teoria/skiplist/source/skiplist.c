#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "skiplist.h"


typedef struct no no_t;

struct no {
    int chave;
    no_t **prox;
};

struct skiplist {
    int nivelMax;
    int nivel;
    no_t *ini;
};

static int verify_alloc(int x) {
    if (!x) {
        printf("Alocação Não efitivada\n");
        return 0;
    }
    return 1;
}

static int qtd_level() {
    int level = 0;
    while (rand() % 2 == 0) {
        level++;
    }

    return level % (NIVEL_MAX + 1);
}

no_t *novo_no(int valor, int level) {
    no_t *n = malloc(sizeof(no_t));
    if (!verify_alloc(n != NULL))
        return NULL;

    n->chave = valor;
    n->prox = malloc((level + 1) *  sizeof(no_t *));

    for (int i = 0; i <= level; i++)
        n->prox[i] = NULL;

    return n;
}

skiplist_t *creat() {
    skiplist_t *sk = malloc(sizeof(skiplist_t));
    if (!verify_alloc(sk != NULL))
        return NULL;

    sk->nivelMax = NIVEL_MAX;
    sk->nivel = 0;

    sk->ini = novo_no(-1, NIVEL_MAX);

    return sk;
}

int search(skiplist_t *sk, int x) {
    if (!verify_alloc(sk != NULL))
        return 0;
    
    no_t *aux = sk->ini;

    for (int i = sk->nivel; i >= 0; i--) {
        while (aux->prox[i] != NULL && aux->prox[i]->chave < x)
            aux = aux->prox[i];
    }
    aux = aux->prox[0];

    if (aux != NULL && aux->chave == x)
        return 1;
    
    return 0;
}

int push (skiplist_t *sk, int x) {
    if (!verify_alloc(sk != NULL))
        return 0;
    
    no_t *aux = sk->ini;
    no_t **update = malloc((NIVEL_MAX + 1) * sizeof(no_t *));

    for (int i = sk->nivel; i >= 0; i--) {
        while (aux->prox[i] != NULL && aux->prox[i]->chave < x)
            aux = aux->prox[i];

        update[i] = aux;
    }
    aux = aux->prox[0];

    if (aux != NULL && aux->chave == x) {
        free(update);
        return 0;
    }

    int node_level = qtd_level();
    no_t *n = novo_no(x, node_level);

    if (node_level > sk->nivel) {
        for (int i = sk->nivel + 1; i <= node_level; i++) {
            update[i] = sk->ini;
        }
        sk->nivel = node_level;
    }

    for (int i = 0; i <= node_level; i++) {
        n->prox[i] = update[i]->prox[i];
        update[i]->prox[i] = n;
    }
    free(update);

    return 1;
}

void show(skiplist_t *sk) {
    if (!verify_alloc(sk != NULL))
        return;

    for (int i = sk->nivel; i >= 0; i--) {
        no_t *n = sk->ini->prox[i];
        printf("Nível %d: ", i);
        while (n != NULL) {
            printf("%d ", n->chave);
            n = n->prox[i];
        }
        printf("\n");
    }
}

int remove_elem(skiplist_t *sk, int x) {
     if (!verify_alloc(sk != NULL))
        return 0;
    
    no_t *aux = sk->ini;
    no_t **update = malloc((NIVEL_MAX + 1) * sizeof(no_t *));

    for (int i = sk->nivel; i >= 0; i--) {
        while (aux->prox[i] != NULL && aux->prox[i]->chave < x)
            aux = aux->prox[i];

        update[i] = aux;
    }
    aux = aux->prox[0];

    if (aux == NULL || aux->chave != x) {
        free(update);
        return 0;
    }

    for (int i = 0; i <= sk->nivel && update[i]->prox[i] == aux; i++) {
        update[i]->prox[i] = aux->prox[i];
    }

    while (sk->ini->prox[sk->nivel] == NULL && sk->nivel > 0) {
        sk->nivel--;
    }

    free(aux->prox);
    free(aux);
    free(update);

    return 1;
}

int kill(skiplist_t *sk) {
    if (!verify_alloc(sk != NULL))
        return 0;

    no_t *aux = sk->ini;

    while (aux != NULL) {
        no_t *n = aux;
        aux = aux->prox[0];
        free(n->prox);
        free(n);
    }
    free(sk);

    return 1;
}

int alter(skiplist_t *sk, int x) {
    if (!verify_alloc(sk != NULL))
        return 0;
    
    no_t *aux = sk->ini;

    for (int i = sk->nivel; i >= 0; i--) {
        while (aux->prox[i] != NULL && aux->prox[i]->chave < x)
            aux = aux->prox[i];

    }
    aux = aux->prox[0];

    if (aux == NULL || aux->chave != x) {
        return 0;
    }

    aux->chave = x;

    return 1;
}