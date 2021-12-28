#include <stdio.h>
#include <stdlib.h>
#include "banco.h"

int main() {
    banco_t *b = criar();

    inserir(b, 1);
    inserir(b, 2);
    inserir(b, 3);
    inserir(b, 4);
    inserir(b, 5);
    inserir(b, 6);
    inserir(b, 7);

    elem x;
    while(!esta_vazio(b)) {
        remover(b, &x);
        printf("%d ", x);
    }
    printf("\n");

    liberar(b);

    return EXIT_SUCCESS;
}