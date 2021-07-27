/*---------------------------------------------------------------------- 
                    Universidade de São Paulo
        Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main () {
    
    char spam[12][9] = {"gratuito", "atencao", "urgente", "imediato", "zoombie", "oferta", "dinheiro", "renda", "fundo", "limitado", "ajuda", "SOS"};
    char caracterer, palavraArmazenada[77] = "\0";
    int tamanhoLinha = 0, indicePalavra = 0, palavraErrada = 0;
    
    while (1) {

        caracterer = getchar();

        if (caracterer == EOF) {
            printf("Inbox\n"); 
            break;
        }

        tamanhoLinha++;

        if(!isspace(caracterer)) {

            palavraArmazenada[indicePalavra] = caracterer;

            for (int j = 0; j < 12; j++) {
                if (strcmp(spam[j], palavraArmazenada) == 0) {
                    palavraErrada++;
                }
            }

            indicePalavra++;
        }
        else {
            for (int j = 0; j < 77; j++) {
                palavraArmazenada[j] = '\0';
            }
            indicePalavra = 0;

            if(caracterer == '\n' || caracterer == '\r') {
                tamanhoLinha = 0;
            }
        }

        if (tamanhoLinha > 76 || palavraErrada >= 2) {
            printf("Spam\n");
            exit(0);
        }     
    }

    return 0;
}