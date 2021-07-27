/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>

int main() {
    
    char entrada;
    int contador = 0;
    int coordenadaX = 0;
    int coordenadaY = 0;

    while (contador < 6) {
        scanf ("%c", &entrada);

        switch (entrada) {
            case 'W':
                coordenadaY = coordenadaY + 1;
                break;

            case 'S':
                coordenadaY = coordenadaY - 1;
                break;

            case 'A':
                coordenadaX = coordenadaX - 1;
                break;

            case 'D':
                coordenadaX = coordenadaX + 1;
                break;
        }
        contador++;
    }
    
    printf("%d %d\n", coordenadaX, coordenadaY);

    return 0;
}