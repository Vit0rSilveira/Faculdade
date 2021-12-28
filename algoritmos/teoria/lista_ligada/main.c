#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main() {

    lista_t *l = criar();

    inserir(l, 5);
    inserir(l, 2);
    inserir(l, 3);
    inserir(l, 7);
    inserir(l, 10);
    
    imprimir(l);

    remover(l, 10);
    imprimir(l);

    liberar(l);

    return 0;
}