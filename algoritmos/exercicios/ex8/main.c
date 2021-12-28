#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "polinomio.h"

int main(int argc, char *argv[]) {
    int t;
    scanf(" %d", &t);

    for (int i  = 0; i < t; i++) {
        polynomial_t *p = creat_polynomial();

        int qtd;
        scanf(" %d", &qtd);
        for (int j = 0; j < qtd; j++)
            add_polynomial(p);

        list_t *sum = sum_polynomial(p);
        show_p(sum);

        free_polynomial(p);
        free_list(sum);
    }
    
    return EXIT_SUCCESS;
}