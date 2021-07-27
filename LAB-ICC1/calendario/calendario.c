/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>

int main() {

    int dia;
    scanf ("%d", &dia);

    // Cabeçalho padrão que não muda.
    printf ("         Abril 2021         \n");
    printf (" Do  Se  Te  Qu  Qu  Se  Sa \n");
    printf ("                ");

    for (int i = 1; i <= 30; i++) {

        if (i == dia && (i == 3 || i == 10 || i == 17 || i == 24)) {
            printf("(%2d)\n", i);
        }
        else if (i == 3 || i == 10 || i == 17 || i == 24) {
            printf(" %2d \n", i);
        }
        else if (i == dia) {
            printf("(%2d)", i);
        }
        
        else {
            printf(" %2d ", i);
        }
        
    }
    return 0;
}