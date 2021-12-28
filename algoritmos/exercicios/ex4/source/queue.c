#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

struct queue {
    void **itens;
    int head;
    int tail;
    int qtd;
    int tamItens;
};

static void my_assert(int teste) {
    if(!teste)
        exit(0);
}

queue_t *create_queue(int tamItens) {
    queue_t *q = malloc(sizeof(queue_t));
    my_assert(q != NULL);

    q->itens = calloc(MAX, sizeof(void *));

    q->tamItens = tamItens;

    q->head = 0;
    q->tail = 0;
    q->qtd = 0;

    return q;
}

int is_empty(queue_t *q) {
    my_assert(q != NULL);

    if(q->qtd == 0)
        return 1;

    return 0;
}

int is_full(queue_t *q) {
   my_assert(q != NULL);

    if(q->qtd == MAX)
        return 1;
    
    return 0;
}

void push(queue_t *q, void *item) {
    if(is_full(q)) {
        printf("FILA CHEIA\n");
        return;
    }

    q->itens[q->head] = malloc(q->tamItens);
    my_assert(q->itens[q->head] != NULL);

    memcpy(q->itens[q->head], item, q->tamItens);

    q->qtd++;
    q->head++;
}

void *pop(queue_t *q) {
    if(is_empty(q)) {
        printf("FILA VAZIA\n");
        return NULL;
    }

    q->qtd--;
    q->tail++;

    return q->itens[q->tail - 1];
}

void delete_queue(queue_t *q, free_fun delete_item){
    while(!is_empty(q)) {
        void *tmp = pop(q);
        delete_item(tmp);
    }
    free(q->itens);
    free(q);
}