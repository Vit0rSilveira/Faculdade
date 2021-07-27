/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    
    char caracter, caracterePassado = '\0';
    int numeroLinhas = 0, numeroPalavras = 1, numeroChars = 0;

    while(1) {

        caracter = getchar();

        if (caracter == EOF) {
            break;
        }
        
        numeroChars++;

        if (caracter == '\n' || caracter == '\r') {
            numeroLinhas++;
        }
        if (caracter == '\n' && caracterePassado == '\r') {
            numeroLinhas--;
        }
    
        if (isspace(caracterePassado) && !isspace(caracter)) { // isspace retorna true se é espaço, tab e nova linha.
            numeroPalavras++;
        }
        
        caracterePassado = caracter;

    }

    printf("Linhas\tPalav.\tCarac.\n");
    printf("%d\t%d\t%d\n", numeroLinhas, numeroPalavras, numeroChars);

    return 0;
}