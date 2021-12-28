#ifndef LIST_H
#define LIST_H

typedef struct list list_t;
typedef int elem;


list_t *creat_list();
void push_list(list_t *l, elem x);
void remove_elem_list(list_t *l, elem x);
void free_list(list_t *l);
void show_list(list_t *l, void (*show_elem)(elem, int, int));
int size_list(list_t *l);
void access_elements(list_t *l1, list_t *l2, void (*func)(elem*, elem*));

#endif