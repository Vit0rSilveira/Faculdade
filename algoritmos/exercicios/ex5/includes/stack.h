#ifndef STACK_H
#define STACK_H

typedef char elem;
typedef struct stack stack_t;


stack_t *creat_stack();

int is_full(stack_t *s);
int is_empty(stack_t *s);

/**
 * @brief show the element at the top of the stack
 * 
 * @param s 
 * @return elem 
 */
elem pick(stack_t *s);

void print_stack(stack_t *s);
void push(stack_t *s, elem x);
void pop(stack_t *s);
void delete_stack(stack_t *s);


#endif