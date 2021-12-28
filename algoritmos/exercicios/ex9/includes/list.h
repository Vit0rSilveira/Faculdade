#ifndef NUM_H
#define NUM_H

typedef char elem;
typedef int boolean;
typedef struct list list_t;

enum teste {FALSE, TRUE};

list_t *creat();
void free_list(list_t *l);

void push_back(list_t *l, elem x);
void push_front(list_t *l, elem x);

void show_list(list_t *l);
int max(list_t *l1, list_t *l2);
int is_big(list_t *l1, list_t *l2);
int min(list_t *l1, list_t *l2);

void sum(list_t *l1, list_t *l2);

#endif