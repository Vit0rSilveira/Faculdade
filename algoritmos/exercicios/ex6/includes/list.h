#ifndef LIST_H
#define LIST_H

#define elem int
typedef struct list list_t;

list_t *creat_list();
void push(list_t *l, elem x);
void print_list(list_t *l);
void delete_list(list_t *l);
void rotate_list(list_t *l, int rotation);

#endif