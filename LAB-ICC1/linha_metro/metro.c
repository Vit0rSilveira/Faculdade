/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>

int main() {

    int estacao;
    scanf("%d", &estacao);


    switch (estacao) {
        case 0:
            printf("* Morumbi\n");
            printf("|\n");
        case 1:
            printf("* Butanta\n");
            printf("|\n");
        case 2:
            printf("* Pinheiros\n");
            printf("|\n");
        case 3:
            printf("* Faria Lima\n");
            printf("|\n");
        case 4:
            printf("* Fradique Coutinho\n");
            printf("|\n");
        case 5:
            printf("* Oscar Freire\n");
            break;
        case 6:
            printf("* Paulista\n");
            printf("|\n");
        case 7:
            printf("* Higienopolis-Mackenzie\n");
            printf("|\n");
        case 8:
            printf("* Republica\n");
            printf("|\n");
        default:
            printf("* Luz\n");
    }


    return 0;
}