/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>

/* Neste código eu tenho um vetor como indice de um vetor, isso porque sempre eu tenho uma operação e depois eu
terei leitura de argumentos(próximos índices do vetor), que são endereços que contem os valores de onde terá 
a mudança a cada interação, por isso um vetor como indice do vetor. */

enum operacoes{HLT, ADD, MUL, CLT, CEQ, JMP, JEQ, CPY, PUT, PTN};

int main() {

    int fita[512];

    for (int j = 0 ; j < 512; j++) {
        scanf("%d", &fita[j]);
    }

    printf("Saida do programa:\n");
    int posicaoExecucao = 0;

    do {

        switch (fita[posicaoExecucao]) {
            case ADD :
                fita[fita[posicaoExecucao + 3]] = fita[fita[posicaoExecucao + 1]] + fita[fita[posicaoExecucao + 2]];
                posicaoExecucao += 4;
                break;
            case MUL:
                fita[fita[posicaoExecucao + 3]] = fita[fita[posicaoExecucao + 1]] * fita[fita[posicaoExecucao + 2]];
                posicaoExecucao += 4;
                break;
            case CLT:
                if (fita[fita[posicaoExecucao + 1]] < fita[fita[posicaoExecucao + 2]]) {
                    fita[fita[posicaoExecucao + 3]] = 1;
                }
                else {
                    fita[fita[posicaoExecucao + 3]] = 0;
                }
                posicaoExecucao += 4;
                break;
            case CEQ:
                if (fita[fita[posicaoExecucao + 1]] == fita[fita[posicaoExecucao + 2]]) {
                    fita[fita[posicaoExecucao + 3]] = 1;
                }
                else {
                    fita[fita[posicaoExecucao + 3]] = 0;
                }
                posicaoExecucao += 4;
                break;
            case JMP:
                posicaoExecucao = fita[fita[posicaoExecucao + 1]];
                break;
            case JEQ:
                if (fita[fita[posicaoExecucao + 1]] != 0) {
                    posicaoExecucao = fita[fita[posicaoExecucao + 2]];
                }
                else {
                    posicaoExecucao += 3;
                }
                break;
            case CPY:
                fita[fita[posicaoExecucao + 2]] = fita[fita[posicaoExecucao + 1]];
                posicaoExecucao += 3;
                break;
            case PUT:
                printf("%c", fita[fita[posicaoExecucao + 1]]);
                posicaoExecucao += 2;
                break;
            case PTN:
                printf("%d", fita[fita[posicaoExecucao + 1]]);
                posicaoExecucao += 2;
                break;
            default:
                posicaoExecucao += 3;
                break;
        }
        
    }
    while (fita[posicaoExecucao] != HLT);

    printf("\nEstado final da fita:\n"); 
    for (int i = 0; i < 512; i++) {
        printf("%d\n", fita[i]);
    }

    return 0;
}