#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "heap.h"

struct no {
    elem info;
    int prio;
};

struct fila {
    int n;
    no_t *heap[MAX];
};

/* sobe o elemento i no heap */
static void sobe(fila_t *f, int i) {
    int j; /* índice do pai de i */
    no_t *temp; /* variável usada na troca (swap) */
    j = (int)((i-1)/2);
    /* se i tem pai e que seja menor que i */
    if(j >= 0 && f->heap[i]->prio > f->heap[j]->prio) {
        /* troca ambos */
        temp = f->heap[i];
        f->heap[i] = f->heap[j];
        f->heap[j] = temp;
        /* e continua subindo este elemento */
        sobe(f, j);
    }
}

/* desce o elemento i no heap de tamanho n */
static void desce(fila_t *f, int i) {
    int j; /* índice do filho de i */
    no_t *temp; /* variável usada na troca (swap) */
    j = 2*i + 1;
    if(j < f->n) { /* se i tem filhos */
        if(j < f->n - 1) { /* se i tem filho direito */
        /* pega o maior filho... */
            if(f->heap[j]->prio < f->heap[j+1]->prio)
                j++;
        }
        /* ..e compara com o pai */
        if(f->heap[j]->prio > f->heap[i]->prio) {
            /* troca ambos (swap) */
            temp = f->heap[i];
            f->heap[i] = f->heap[j];
            f->heap[j] = temp;
            /* e continua descendo o mesmo elemento */
            desce(f, j);
        }
    }
}

fila_t *criar() {
    fila_t *f = malloc(sizeof(fila_t));
    f->n = 0;
    
    return f;
}

int inserir(fila_t *f, elem chave, int prio) {
    if (!isFull(f)) {
        no_t *p = malloc(sizeof(no_t));
        p->info = chave;
        p->prio = prio;

        f->heap[f->n] = p;
        sobe(f, f->n);
        f->n++;
        return 1;
    }
    
    return 0;
}

int remover(fila_t *f, elem *chave) {
    if (!isEmpty(f)) {
        *chave = f->heap[0]->info;
        free(f->heap[0]);

        f->n--;
        f->heap[0] = f->heap[f->n];
        desce(f, 0);

        return 1;
    }

    return 0;
}

int isEmpty(fila_t *f) {
    assert(f != NULL);

    return f->n == 0;
}

int isFull(fila_t *f) {
    assert(f != NULL);

    return f->n == MAX;
}

void finalizar(fila_t *f) {
    for (int i = 0; i < f->n; i++)
        free(f->heap[i]);
    free(f);
}
