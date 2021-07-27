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

enum operadores {DIGITO, OPERADOR, FIM};

#define EH_OPERACAO(c) (c == '+' || c == '-' || c == '/' || c == '*')

double calcular();


int main() {

    double resultado = calcular();
    
    printf("Resultado: %.6lf\n", resultado);

    return 0;
}

int espiar() {
    int espiao = -1;
    char caractere;
    caractere = getchar();
    
    if (caractere != ' ') {
        if(isdigit(caractere))
            espiao = DIGITO;
        else if (caractere == EOF)
            espiao = FIM;
        else if (EH_OPERACAO(caractere))
            espiao = OPERADOR;
        ungetc(caractere, stdin);
    }

    return espiao;
}

double calcular() {
    double *stack = NULL;
    double entrada;
    char operador;
    int qtdStack = 0;
    int espiao;

    do {
        espiao = espiar();
        double operacao;

        if(espiao == DIGITO) {
            scanf("%lf", &entrada);
            stack = realloc(stack, ++qtdStack * sizeof(double));
            stack[qtdStack - 1] = entrada;
        }
        else if (espiao == OPERADOR) {
            operador = getchar();
            switch(operador) {
                case '+':
                    operacao = stack[qtdStack - 2] + stack[qtdStack - 1];
                    break;
                case '-':
                    operacao = stack[qtdStack - 2] - stack[qtdStack - 1];
                    break;
                case '*':
                    operacao = stack[qtdStack - 2] * stack[qtdStack - 1];
                    break;
                case '/':
                    operacao = stack[qtdStack - 2] / stack[qtdStack - 1];
                    break;
            }
            stack = realloc(stack, --qtdStack * sizeof(double));
            stack[qtdStack - 1] = operacao;
        }   
    } while (espiao != FIM);

    double resultado = stack[0];
    free(stack);

    return resultado;
}
