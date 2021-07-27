/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>

int main() {

    double nota1, nota2, nota3, nota4, media, minimo;
    scanf("%lf %lf %lf %lf", &nota1, &nota2, &nota3, &nota4);

    minimo = nota1;
    if (nota2 < minimo) {
        minimo = nota2;
    }
    if (nota3 < minimo) {
        minimo = nota3;
    }
    if (nota4 < minimo) {
        minimo = nota4;
    }

    media = (nota1 + nota2 + nota3 + nota4 - minimo) / 3;
    printf("%.4lf\n", media);


    return 0;

}