#ifndef QUEUE_H
#define QUEUE_H

#define MAX 100

typedef struct queue queue_t;
typedef void (*free_fun)(void *);


queue_t *create_queue(int tamItens);

int is_empty(queue_t *q);
int is_full(queue_t *q);

void push(queue_t *q, void *item);
void *pop(queue_t *q);

void delete_queue(queue_t *q, free_fun delete_item);

#endif