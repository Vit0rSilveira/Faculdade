#include <stdio.h>
#include <stdlib.h>
#include "abb.h"


int main(int argc, char *argv[]) {
    arvore_t *a = criar();

    inserir (&a->raiz, 5);
    inserir (&a->raiz, 3);
    inserir (&a->raiz, 7);
    inserir (&a->raiz, 9);
    inserir (&a->raiz, 8);
    inserir (&a->raiz, 2);

    imprimir(a->raiz);
    printf("\n");
    remover(&a->raiz, 5);
    imprimir(a->raiz);
    printf("\n");

    finalizar(a->raiz);
    free(a);

    return EXIT_SUCCESS;
}