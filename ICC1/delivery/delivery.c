/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define BALDIO -1
#define RESIDENCIAL 0
#define PARQUE 1

float distanciaEuclides(int quantidade, int largura[], int altura[], int terreno[]);
float distanciaHerman(int quantidade, int largura[], int altura[], int terreno[]);

int main() {

    int pontosPlano;
    scanf("%d", &pontosPlano);

    if (pontosPlano <= 0) {
        printf("Falha no processamento dos dados.\n");
        exit(0);
    }

    int pontoX[pontosPlano], pontoY[pontosPlano], tipoTerreno[pontosPlano];

    for (int i = 0; i < pontosPlano; i++) {
        
        scanf("%d %d %d", &pontoX[i], &pontoY[i], &tipoTerreno[i]);
        if (tipoTerreno[i] < -1 || tipoTerreno[i] > 1) {
            printf("Falha no processamento dos dados.\n");
            exit(0);
        }
    }

    int tBaldio = 0, tResidencial = 0, tParque = 0;
    for (int i = 0; i < pontosPlano; i++) {
        if (tipoTerreno[i] == BALDIO) {
            tBaldio++;
        }
        else if (tipoTerreno[i] == RESIDENCIAL) {
            tResidencial++;
        }
        else {
            tParque++;
        }
    }
    
    float euclides = distanciaEuclides(pontosPlano, pontoX, pontoY, tipoTerreno);
    float herman = distanciaHerman(pontosPlano, pontoX, pontoY, tipoTerreno);
    float distancia = herman - euclides;
    printf("Ao todo, foi passado por %d terrenos baldios, %d terrenos residenciais e %d parques.\n",tBaldio, tResidencial, tParque);
    printf("A diferenca total de distancia percorrida foi de %.2f metros.\n", distancia);

    return 0;
}
float distanciaEuclides(int quantidade, int largura[], int altura[], int terreno[]) {

    float distEuclides = 0.0;
    for (int i = 0; i < quantidade; i++) {
        if (i != (quantidade - 1)) {
            if (terreno[i] == RESIDENCIAL) {
                distEuclides += fabs(largura[i + 1] - largura[i]) + fabs(altura[i + 1] - altura[i]);
            }
            else {
                distEuclides += sqrt(pow((largura[i + 1] - largura[i]), 2) + pow((altura[i + 1] - altura[i]), 2));
            }
        }
        else {
            if (terreno[i] == RESIDENCIAL) {
                distEuclides += fabs(largura[i] - largura[0]) + fabs(altura[i] - altura[0]);
            }
            else {
                distEuclides += sqrt(pow((largura[i] - largura[0]), 2) + pow((altura[i] - altura[0]), 2));
            }
        }
    }
    return distEuclides;
}
float distanciaHerman(int quantidade, int largura[], int altura[], int terreno[]) {

    float distHerman = 0.0;
    for (int i = 0; i < quantidade; i++) {
        if (i != (quantidade - 1)) {
            if (terreno[i] == BALDIO) {
                distHerman += sqrt(pow((largura[i + 1] - largura[i]), 2) + pow((altura[i + 1] - altura[i]), 2));
            }
            else {
                distHerman += fabs(largura[i + 1] - largura[i]) + fabs(altura[i + 1] - altura[i]);
            }
        }
        else {
            if (terreno[i] == BALDIO) {
                distHerman += sqrt(pow((largura[i] - largura[0]), 2) + pow((altura[i] - altura[0]), 2));
            }
            else {
                distHerman += fabs(largura[i] - largura[0]) + fabs(altura[i] - altura[0]);
            }
        }
    }
    return distHerman;
}