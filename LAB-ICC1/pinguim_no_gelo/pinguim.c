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

    int rodadas, jogadores, posicao;
    scanf("%d %d %d", &rodadas, &jogadores, &posicao);

    if (posicao == jogadores) {
        posicao = 0;
    }

    // Contador controla a rodada atual (linhas que está) e o fim dos prints.
    int contador = 0; 

    // For para percorrer todas as rodadas, sem verificar rodada a rodada.
    for (int i = 1; i <= rodadas; i++) {

        // For para printar pinguim.
        for (int j = 0; j < i; j++) {
            contador++;
            if (contador % jogadores == posicao) {
                if (contador == 1 && posicao == 1) {
                printf ("%d pinguim\n", j);
                }
                else {
                    printf ("%d pinguins\n", j);
                }     
            }
            if (contador == rodadas) {
                    exit (0);
            } 
        }
        // For para printar no gelo.
        for (int j = 0; j < i; j++) {
            contador++;
            if (contador % jogadores == posicao) {
                printf ("no gelo\n");
            }
            if (contador == rodadas) {
                exit (0);
            }  
        }

        // For para  uhuu.
        for (int j = 0; j < i; j++) {
            contador++;
            if (contador % jogadores == posicao) {
                printf ("uhuu!\n");
            }
            if (contador == rodadas) {
                exit (0);
            }
        }
    }
    return 0;
}