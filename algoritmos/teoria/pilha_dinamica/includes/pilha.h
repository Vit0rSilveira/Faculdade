#ifndef PILHA
#define PILHA

#define tamPilha 100

typedef struct pilha stack_t;

stack_t *create(int tamElem);

void destroy(stack_t *p);
int isFull(stack_t *p);
int isEmpty(stack_t *p);

int push(stack_t *p, void *x);
int pop(stack_t *p, void *x);
int top(stack_t *p, void *x);

#endif