#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "data.h"

struct stack {
    int top;
    int tamStack;
    elem *stack;
};

static void my_assert(int verify) {
    if(verify)
        exit(0);
}

void print_stack(stack_t *s) {
    for(int i = 0; i < s->tamStack; i++)
        printf("%c", s->stack[i]);
    
    printf("\n");
}

stack_t *creat_stack() {
    stack_t *s = malloc(sizeof(stack_t));
    my_assert(s == NULL);

    s->stack = NULL;
    s->tamStack = 0;
    s->top = -1;

    return s;
}

int is_full(stack_t *s) {
    my_assert(s == NULL);

    if(s->top == (SIZE - 1))
        return 1;
    
    return 0;
}

int is_empty(stack_t *s) {
    my_assert(s == NULL);

    if(s->top == -1)
        return 1;

    return 0;
}

void push(stack_t *s, elem x) {
    my_assert(s == NULL);

    if(is_full(s)) {
        printf("Stack is Full\n");
        return;
    }

    s->stack = realloc(s->stack, ++(s->tamStack) * sizeof(elem));

    s->top += 1;
    s->stack[s->top] = x;
}

void pop(stack_t *s) {
    my_assert(s == NULL);

    if(is_empty(s)) {
        printf("Stack is Empty\n");
        return;
    }
    s->top -= 1;
}

elem pick(stack_t *s) {
    if(s->top < 0)
        return '\0';
        
    char top = s->stack[s->top];

    return top;
}

void delete_stack(stack_t *s) {
    free(s->stack);
    free(s);
}