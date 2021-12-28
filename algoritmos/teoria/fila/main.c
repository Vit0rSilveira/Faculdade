#include <stdio.h>
#include "fila.h"

int main() {
    fila_t *f = criar();

    for (int i = 0; i < 10; i++)
        inserir(f,i);

    elem x;
    while (!isEmpty(f)) {
        remover(f, &x);
        printf("%d ", x);
    }
    printf("\n");
    
    destruir(f);

    return 0;
}