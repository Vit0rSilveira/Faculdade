#ifndef LISTA_H
#define LISTA_H

typedef int elem;
typedef struct lista lista_t;

lista_t *criar();
void liberar(lista_t *l);
void inserir(lista_t *l, elem x);
int tamanho(lista_t *l);
void imprimir (lista_t *l);
int esta_na_lista(lista_t *l, elem x);
int remover(lista_t *l, elem x);


#endif