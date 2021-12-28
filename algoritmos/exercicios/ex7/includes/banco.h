#ifndef BANCO_H
#define BANCO_H

typedef struct banco banco_t;

banco_t *creat();
void imprimir(banco_t *b);
int is_empty(banco_t *b);
void insert(banco_t *b, int code, char *name);
void remove_elem(banco_t *b, int code);
void free_bank(banco_t *b);

#endif