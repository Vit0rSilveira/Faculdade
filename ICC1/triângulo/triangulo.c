/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

int main() {

    int linhas;
    char caractere;
    scanf("%d\n%c", &linhas, &caractere);

    if (linhas > 25 || linhas < 0 || linhas == 0) {

        printf("Altura invalida\n");
        exit(1);
    }

    for (int l = 0; l < linhas; l++) {

        // For para os espaços.
        for (int e = 0; e < linhas - l - 1 ; e++) {

            printf(" ");

        }

        // For para os caracteres
        // Numero caracteres = 2 * linha + 1.
        for (int c = 0; c < 2 * l + 1; c++) {

            printf("%c", caractere);
        }
        
        printf("\n");
    }

    return 0;
}