/*----------------------------------------------------------------------
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651
---------------------------------------------------------------------- */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum operacoes {DIGITO, CARACTERE, FIM, BRANCO};

#define EH_OPERADOR(c) (c == '+'|| c == '-' || c == '/' || c == '*')


int espiar();
double calcularExpressao();


int main() {

    do {

        double resultado = calcularExpressao();
        printf("%.6lf\n", resultado);
        scanf(" ");

    } while (!feof(stdin));

    return 0;
}

int espiar() {
    int espiao = -1;
    char caractere = getchar();

    if (caractere == ' ')
        return espiar();

    else if (isdigit(caractere))
        espiao = DIGITO;

    else if (caractere == ')') {
        espiao = FIM;
        return espiao;
    }
    else
        espiao = CARACTERE;

    ungetc(caractere, stdin);

    return espiao;
}

double calcularExpressao() {
    int espiao = espiar();
    double resultado = 0;
    char caractere;

    if (espiao == FIM) {
        return resultado;
    }

    else if (espiao == CARACTERE) {
        caractere = getchar();

        if (caractere == '(') {
            resultado = calcularExpressao();
            resultado += calcularExpressao();
        }

        else if (EH_OPERADOR(caractere)) {
            switch(caractere) {
                case '+':
                    resultado = calcularExpressao() + calcularExpressao();
                    break;
                case '-':
                    resultado = calcularExpressao() - calcularExpressao();
                    break;
                case '*':
                    resultado = calcularExpressao() * calcularExpressao();
                    break;
                case '/':
                    resultado = calcularExpressao() / calcularExpressao();
                    break;
            }
        }
    }
    else if (espiao == DIGITO) {
        double valor;
        scanf("%lf", &valor);
        return valor;
    }

    return resultado;
}