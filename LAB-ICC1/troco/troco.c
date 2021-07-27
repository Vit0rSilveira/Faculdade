/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>

void executaTroco(int troco, int *real1, int *cents50, int *cents25,  int *cents10, int *cents5, int *cents1);

int main() {
    int troco;
    scanf("%d", &troco);

    int real1, cents50, cents25, cents10, cents5, cents1;
    executaTroco(troco,&real1, &cents50, &cents25, &cents10, &cents5, &cents1);
    printf("O valor consiste em %d moedas de 1 real\n", real1);
    printf("O valor consiste em %d moedas de 50 centavos\n", cents50);
    printf("O valor consiste em %d moedas de 25 centavos\n", cents25);
    printf("O valor consiste em %d moedas de 10 centavos\n", cents10);
    printf("O valor consiste em %d moedas de 5 centavos\n", cents5);
    printf("O valor consiste em %d moedas de 1 centavo\n", cents1);

    return 0;
}

void executaTroco(int troco, int *real1, int *cents50, int *cents25, int *cents10, int *cents5, int *cents1) {
        *real1 = 0;
        *cents50 = 0;
        *cents25 = 0;
        *cents10 = 0;
        *cents5 = 0;
        *cents1 = 0;
        
        int centavos = troco % 100;
        *real1 = (troco - centavos) / 100;

        if (centavos / 50 > 0) {
            *cents50 = centavos / 50;
            centavos = centavos - *cents50 * 50;
        }
        if (centavos / 25 > 0) {
            *cents25 = centavos / 25;
            centavos = centavos - *cents25 * 25;
        }
        if (centavos / 10 > 0) {
            *cents10 = centavos / 10;
            centavos = centavos - *cents10 * 10;
        }
        if (centavos / 5 > 0) {
            *cents5 = centavos / 5;
            centavos = centavos - *cents5 * 5;
        }
        if (centavos / 1 > 0)
            *cents1 = centavos / 1;
}
