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

    int pixels[25], cores[6];

    for (int i = 0; i < 4; i++) {
        cores[i] = 0;
    }

    for (int i = 0; i < 25; i++) {

        scanf(" %d", &pixels[i]);
        
        if (pixels[i] == 0) {
            cores[0]++;
        }
        else if (pixels[i] == 1) {
            cores[1]++;
        }
        else if (pixels[i] == 2) {
            cores[2]++;
        }
        else if (pixels[i] == 3) {
            cores[3]++;
        }
        else if (pixels[i] == 4) {
            cores[4]++;
        }
    }
    for (int i = 0; i < 5; i++) {
        printf("%d: |", i);
        for (int j = 0; j < cores[i]; j++) {
            printf("#");
        }
        printf("\n");
    }
    
    int maior = cores[0], maiorCor = 0;
    for (int i = 0; i < 5; i++) {
        if (cores[i] > maior) {
            maior = cores[i];
            maiorCor = i;
        }
    }    
    for (int i = 0; i < 25; i++) {
        if (pixels[i] == maiorCor) {
            printf("%d\n", i);
        }
    }
    
    return 0;
}