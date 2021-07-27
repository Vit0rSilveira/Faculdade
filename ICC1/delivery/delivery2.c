/*---------------------------------------------------------------------- 
                    Universidade de São Paulo
        Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define BALDIO -1
#define RESIDENCIAL 0
#define PARQUE 1

void contaTerrenos(int quantidade, int terreno[], int *tBaldio, int *tResidencial, int *tParque);
float distanciaEuclides(int quantidade, int largura[], int altura[], int terreno[]);
float distanciaHerman(int quantidade, int largura[], int altura[], int terreno[]);


int main() {
    int quantidade;
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf("Falha no processamento dos dados.\n");
        exit(0);
    }

    int largura[quantidade], altura[quantidade], terreno[quantidade];
    for (int i = 0; i < quantidade; i++) {
        
        scanf("%d %d %d", &largura[i], &altura[i], &terreno[i]);
        if (terreno[i] < -1 || terreno[i] > 1) {
            printf("Falha no processamento dos dados.\n");
            exit(0);
        }
    }

    int tBaldio, tResidencial, tParque;
    contaTerrenos(quantidade, terreno, &tBaldio, &tResidencial, &tParque);
    
    float euclides = distanciaEuclides(quantidade, largura, altura, terreno);
    float herman = distanciaHerman(quantidade, largura, altura, terreno);
    float distancia = herman - euclides;

    printf("Ao todo, foi passado por %d terrenos baldios, %d terrenos residenciais e %d parques.\n",tBaldio, tResidencial, tParque);
    printf("A diferenca total de distancia percorrida foi de %.2f metros.\n", distancia);

    return 0;
}

float diagonal(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int borda(int x1, int y1, int x2, int y2) {
    return fabs(x2 - x1) + fabs(y2 - y1);
}

float distanciaEuclides(int quantidade, int largura[], int altura[], int terreno[]) {
    float distancia = 0.0;

    for (int i = 0; i < quantidade - 1; i++) {
        if (terreno[i] == RESIDENCIAL)
            distancia += borda(largura[i], altura[i], largura[i + 1], altura[i + 1]);
        else
            distancia += diagonal(largura[i], altura[i], largura[i + 1], altura[i + 1]);
    }

    if (terreno[quantidade - 1] == RESIDENCIAL)
        distancia += borda(largura[quantidade - 1], altura[quantidade - 1], largura[0], altura[0]);
    else
        distancia += diagonal(largura[quantidade - 1], altura[quantidade - 1], largura[0], altura[0]);
    
    return distancia;
}

float distanciaHerman(int quantidade, int largura[], int altura[], int terreno[]) {
    float distancia = 0.0;

    for (int i = 0; i < quantidade - 1; i++) {
        if (terreno[i] == BALDIO)
            distancia += diagonal(largura[i], altura[i], largura[i + 1], altura[i + 1]);
        else
            distancia += borda(largura[i], altura[i], largura[i + 1], altura[i + 1]);
    }

    if (terreno[quantidade - 1] == BALDIO)
        distancia += diagonal(largura[quantidade - 1], altura[quantidade - 1], largura[0], altura[0]);
    else
        distancia += borda(largura[quantidade - 1], altura[quantidade - 1], largura[0], altura[0]);

    return distancia;
}

void contaTerrenos(int quantidade, int terreno[], int *tBaldio, int *tResidencial, int *tParque) {
    *tBaldio = 0;
    *tResidencial = 0;
    *tParque = 0;

    for (int i = 0; i < quantidade; i++) {
        if (terreno[i] == BALDIO)
            (*tBaldio)++;
        else if (terreno[i] == RESIDENCIAL)
            (*tResidencial)++;
        else
            (*tParque)++;
    }
}
