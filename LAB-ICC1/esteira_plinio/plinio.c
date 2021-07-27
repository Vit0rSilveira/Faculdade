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
    
    char esteira[32][65];
    int linhaInicio, colunaInicio;

    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 65; j++) {
            scanf("%c", &esteira[i][j]);
        }
    }
    
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 65; j++) {
            if (esteira[i][j] == '[') {
                linhaInicio = i;
                colunaInicio = j;
            }
        }
    }

    int linhaAtual = linhaInicio, colunaAtual = colunaInicio + 2, fimEsteira = 0;
    char charAnterior; // Armazena o caractere anterior, antes de virar um '.'
    while (fimEsteira == 0) {

        switch (esteira[linhaAtual][colunaAtual]) {

        case '>':
            charAnterior = esteira[linhaAtual][colunaAtual];
            esteira[linhaAtual][colunaAtual] = '.';
            colunaAtual += 2; 
            break;
        case 'v':
            charAnterior = esteira[linhaAtual][colunaAtual];
            esteira[linhaAtual][colunaAtual] = '.';
            linhaAtual += 1;
            break;
        case '<':
            charAnterior = esteira[linhaAtual][colunaAtual];
            esteira[linhaAtual][colunaAtual] = '.';
            colunaAtual -= 2;
            break;
        case '^':
            charAnterior = esteira[linhaAtual][colunaAtual];
            esteira[linhaAtual][colunaAtual] = '.';
            linhaAtual -= 1;
            break;
        case '#':
            if (charAnterior == '>') {
                colunaAtual += 2;
            }
            else if (charAnterior == 'v') {
                linhaAtual += 1;
            }
            else if (charAnterior == '<') {
                colunaAtual -= 2;
            }
            else if (charAnterior == '^' ) {
                linhaAtual -= 1;
            }
            else {
                printf("ERRO\n");
            }
            break;
        case ' ':
            printf("Falha na esteira.\n");
            fimEsteira = 1;
            break;
        case ']':
            printf("Ok.\n");
            fimEsteira = 1;
            break;
        case '.':
            printf("Loop infinito.\n");
            fimEsteira = 1;
            break;
        default:
            printf("ERRO.\n");
           break;
        }
    }
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 65; j++) {
            printf("%c", esteira[i][j]);
        }
    }
    return 0;
}