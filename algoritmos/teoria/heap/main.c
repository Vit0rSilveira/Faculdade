#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


int main(int argc, char *argv[]) {

    fila_t *f = criar();
    inserir(f, 4, 5);
    inserir(f, 7, 1);
    inserir(f, 2, 3);
    inserir(f, 8, 9);

    elem x;
    while (!isEmpty(f)) {
        remover(f, &x);
        printf("%d ", x);
    }
    printf("\n");

    finalizar(f);

    return EXIT_SUCCESS;
}