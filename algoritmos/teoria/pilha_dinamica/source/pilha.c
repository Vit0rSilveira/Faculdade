#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "pilha.h"

struct pilha {
    int top;
    void **itens;
    int tamElem;
};

stack_t *create(int tamElem) {
    stack_t *p = (stack_t *)malloc(sizeof(stack_t));
    assert(p != NULL);


    p->itens = (void **)malloc(sizeof(void *) * tamPilha);
    assert(p->itens != NULL);

    p->top = -1;
    p->tamElem = tamElem;

    return p;
}

void destroy(stack_t *p) {
    
    while(p->top >= 0) {
        free(p->itens[p->top]);
        p->top -= 1;
    }

    if (p->itens != NULL)
        free(p->itens);

    if(p != NULL)
        free(p);
    
    p = NULL;
}

int isFull(stack_t *p) {
    assert(p != NULL);

    if (p->top == tamPilha - 1)
        return 1;
    else
        return 0;
}

int isEmpty(stack_t *p) {
    assert(p != NULL);

    if (p->top == -1)
        return 1;
    else
        return 0;
}

int push(stack_t *p, void *x) {
    assert(p != NULL);

    if (isFull(p) == 1)
        return -1;
    
    p->top = p->top + 1;

    p->itens[p->top] = (void *)malloc(p->tamElem);
    assert(p->itens[p->top] != NULL);
   
    memcpy(p->itens[p->top], x, p->tamElem);

    return 1;
}

int pop(stack_t *p, void *x) {
    assert(p != NULL);

    if(isEmpty(p) == 1)
        return -1;

    memcpy(x, p->itens[p->top], p->tamElem);

    free(p->itens[p->top]);

    p->top -= 1;

    return 1;
}

int top(stack_t *p, void *x) {
    assert(p != NULL);

    if(isEmpty(p) == 1)
        return -1;
    
    memcpy(x, p->itens[p->top], p->tamElem);

    return 1;
}