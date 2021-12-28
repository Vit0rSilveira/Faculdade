#ifndef LISTAD_H
#define LISTAD_H

typedef int elem;
typedef struct lista listad_t;

listad_t *criar();
void liberar(listad_t *l);
int inserir(listad_t *l, elem x);
int remover(listad_t *l, elem x);
void imprimir(listad_t *l);
void imprimir_inv(listad_t *l);

#endif