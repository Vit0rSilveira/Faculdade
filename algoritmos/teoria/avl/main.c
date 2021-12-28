#include <stdio.h>
#include <stdlib.h>
#include "avl.h"


int main(int argc, char *argv[]) {
    arvore_t *a = criar();


    finalizar(a->raiz);
    free(a);

    return EXIT_SUCCESS;
}