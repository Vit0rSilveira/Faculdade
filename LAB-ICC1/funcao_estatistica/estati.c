/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>

int maior(int numeros[]);
int menor(int numeros[]);
float media(int numeros[]);
int moda(int numeros[]);

int main() {

    int dados[10];

    for (int i = 0; i < 10; i++) {
        scanf("%d", &dados[i]);
    }

    // Maior
    printf("%d ", maior(dados));
    // Menor
    printf("%d ", menor(dados));
    //Media
    printf("%.2f ", media(dados));
    //Moda
    printf("%d\n", moda(dados));

    return 0;

}

int maior(int numeros[]) {

    int maior = numeros[0];

    for (int i = 1; i < 10; i++) {
        if (maior < numeros[i]) {
            maior = numeros[i];
        }
    }
    return maior;
}

int menor(int numeros[]) {
    int menor = numeros[0];
    for (int i = 1; i < 10; i++) {
        if (menor > numeros[i]) {
            menor = numeros[i];
        }
    }
    return menor;
}

float media(int numeros[]) {

    int somador = 0;
    for (int i = 0; i < 10; i++) {
        somador += numeros[i];
    }
    float media = (float)somador / 10;
    return media;
}

int moda(int numeros[]) {

    int moda, contadorModa = 0, maiorVezes = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (numeros[i] == numeros[j]) {
                contadorModa++;
            }
            if (maiorVezes < contadorModa) {
                maiorVezes = contadorModa;
                moda = numeros[i];
            }
        }
        contadorModa = 0;
    }
    return moda;
}