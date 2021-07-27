/*---------------------------------------------------------------------- 
                    Universidade de São Paulo
        Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>

#define STOP -1

void fillMat(float **mat, int number);
void freeAlocation(float *array, float **mat, int number);


int main() {
    int numberType;
    scanf("%d", &numberType);

    float **matriz = malloc(numberType * sizeof(float *));

    for (int i = 0; i < numberType; i++) {
        matriz[i] = malloc(numberType * sizeof(float));
    }
    
    fillMat(matriz, numberType);

    float *atacks = NULL, valorAtack;
    int index, size = 0;
    while (1) {
        scanf("%f", &valorAtack);

        if (valorAtack == STOP || valorAtack == EOF)
            break;
        scanf("%d", &index);

        atacks = realloc(atacks, (++size) * sizeof(float));
        atacks[index] = valorAtack;
    }

    int attacked;
    scanf("%d", &attacked);

    float hideAtack = 0;
    int indexAtack;
    for (int i = 0; i < numberType; i++) {

        float currentAtack = matriz[i][attacked] * atacks[i];

        if (currentAtack > hideAtack) {
            hideAtack = currentAtack;
            indexAtack = i;
        }
    }

    printf("O melhor ataque possui indice %d e dano %.2f\n", indexAtack, hideAtack);

    freeAlocation(atacks, matriz, numberType);
    
    return 0;
}

void fillMat(float **mat, int number) {
     for (int i = 0; i < number; i++) {
        for (int j = 0; j < number; j++) {
            scanf("%f", &mat[i][j]);
        }
    }

}

void freeAlocation(float *array, float **mat, int number) {
    free(array);

    for (int i = 0; i < number; i++) {
        free(mat[i]);
    }
    free(mat);
}