#ifndef PILHA
#define PILHA

#define tamPilha 100

typedef int elem;
typedef struct pilha stack_t;

stack_t *create();

void destroy(stack_t *p);
int isFull(stack_t *p);
int isEmpty(stack_t *p);

int push(stack_t *p, elem x);
int pop(stack_t *p, elem *x);
int top(stack_t *p, elem *x);

#endif