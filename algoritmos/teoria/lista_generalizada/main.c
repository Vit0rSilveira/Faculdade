#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "listag.h"

int main(void) {
    no_t *l1 = concat(atomo(3), atomo(4));
    no_t *l2 = sublista(l1);
    l2 = concat(l2, atomo(2));
    no_t *l = concat(atomo(1), l2);

    imprimir(l);
    liberar(l);


    return EXIT_SUCCESS;
}