/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */


#include <stdio.h>
#include <stdlib.h>

int const hlt = 0;
int const add = 1;
int const mul = 2;
int const clt = 3;
int const ceq = 4;
int const jmp = 5;
int const jeq = 6;
int const cpy = 7;
int const put = 8;
int const ptn = 9;

/* Neste código eu tenho um vetor como indice de um vetor, isso porque sempre eu tenho uma operação e depois eu
terei leitura de argumentos(próximos índices do vetor), que são endereços que contem os valores de onde terá 
a mudança a cada interação, por isso um vetor como indice do vetor. */

int main() {

    int fita[512];

    for (int j = 0 ; j < 512; j++) {
        scanf("%d", &fita[j]);
    }

    printf("Saida do programa:\n");
    int posicaoExecucao = 0;
    while (1) {

        if (fita[posicaoExecucao] == hlt) {
            break;
        }
        else if (fita[posicaoExecucao] == add) {
            fita[fita[posicaoExecucao + 3]] = fita[fita[posicaoExecucao + 1]] + fita[fita[posicaoExecucao + 2]];
            posicaoExecucao += 4;
        }
        else if (fita[posicaoExecucao] == mul) {
            fita[fita[posicaoExecucao + 3]] = fita[fita[posicaoExecucao + 1]] * fita[fita[posicaoExecucao + 2]];
            posicaoExecucao += 4;
        }
        else if (fita[posicaoExecucao] == clt) {
            if (fita[fita[posicaoExecucao + 1]] < fita[fita[posicaoExecucao + 2]]) {
                fita[fita[posicaoExecucao + 3]] = 1;
            }
            else {
                fita[fita[posicaoExecucao + 3]] = 0;
            }
            posicaoExecucao +=  4;
        }
        else if (fita[posicaoExecucao] == ceq) {
            if (fita[fita[posicaoExecucao + 1]] == fita[fita[posicaoExecucao + 2]]) {
                fita[fita[posicaoExecucao + 3]] = 1;
            }
            else {
                fita[fita[posicaoExecucao + 3]] = 0;
            }
            posicaoExecucao += 4;
        }
        else if (fita[posicaoExecucao] == jmp) {
            posicaoExecucao = fita[fita[posicaoExecucao + 1]];
        }
        else if (fita[posicaoExecucao] == jeq) {
            if (fita[fita[posicaoExecucao + 1]] != 0) {
                posicaoExecucao = fita[fita[posicaoExecucao + 2]];
            }
            else {
                posicaoExecucao += 3;
            }
        }
        else if (fita[posicaoExecucao] == cpy) {
            fita[fita[posicaoExecucao + 2]] = fita[fita[posicaoExecucao + 1]];
            posicaoExecucao += 3;
        }
        else if (fita[posicaoExecucao] == put) {
            printf("%c", fita[fita[posicaoExecucao + 1]]);
            posicaoExecucao += 2;
        }
        else if (fita[posicaoExecucao] == ptn) {
            printf("%d", fita[fita[posicaoExecucao + 1]]);
            posicaoExecucao += 2;
        }
        else {
            posicaoExecucao += 3;
        }
    }

    printf("\nEstado final da fita:\n"); 
    
    for (int i = 0; i < 512; i++) {
        printf("%d\n", fita[i]);
    }

    return 0;
}