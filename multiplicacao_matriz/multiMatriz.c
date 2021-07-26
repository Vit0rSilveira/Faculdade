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
    
    // Declaração da dimensão das matrizes e verificação se podem ser mutiplicadas.
    int linhaA, colunaA, linhaB, colunaB;
    scanf("%d %d %d %d", &linhaA, &colunaA, &linhaB, &colunaB);

    if (colunaA != linhaB || linhaA <= 0 || colunaA <= 0 || linhaB <= 0 || colunaB <= 0) {
        printf("Valores invalidos para a multiplicacao.\n");
        return 0;
    }

    // Declaração da semente
    int semente;
    scanf("%d", &semente);
    srand(semente);

    // Declaração e input das matrizes.
    int matrizA[linhaA][colunaA];
    for (int i = 0; i < linhaA; i++) {
        for (int j = 0; j < colunaA; j++) {
            matrizA[i][j] = rand() % 50 - 25;
        }
    }
    int matrizB[linhaB][colunaB];
    for (int i = 0; i < linhaB; i++) {
        for (int j = 0; j < colunaB; j++) {
            matrizB[i][j] = rand() % 50 - 25;
        }
    }

    // Multiplicação das matrizes.
    int matrizC[linhaA][colunaB];
    for (int i = 0; i < linhaA; i++) {
        for (int j = 0; j < colunaB; j++) {
            matrizC[i][j] = 0;
            // K É a coluna de A ou a linha de B este for serve para eu acessar todos os valores da colunaA e linhaB
            for (int k = 0; k < linhaB; k++) { 
                matrizC[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }

    // Mostrando a matriz C.
    for (int i = 0; i < linhaA; i++) {
        printf("Linha %d: ", i);
        for (int j = 0; j < colunaB; j++) {
            printf("%d ", matrizC[i][j]);
        }
        printf("\n");
    }

    return 0;
}