// Vitor da Silveira Paula - 10689651
/* Neste código, eu faço uma variável contadora para x e uma para o
Caso o contador dê 3 , significa que eu tenho uma linha ou coluna igual o que é vitória. */

#include <stdio.h>

const char mensagem_x[] = "x ganhou";
const char mensagem_o[] = "o ganhou";
const char mensagem_empate[] = "empate";

int main() {

    char jogoVelha[3][3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf(" %c", &jogoVelha[i][j]);
        }
    }

    // Verificação do estados nas linhas.
    int contador_x, contador_o;
    for (int i = 0; i < 3; i++) {
        contador_x = contador_o = 0;
        for (int j = 0; j < 3; j++) {
            if (jogoVelha[i][j] == 'x') {
                contador_x++;
            }
            else if (jogoVelha[i][j] == 'o') {
                contador_o++;
            }

            if (contador_x == 3) {
                printf("%s\n", mensagem_x);
                return 0;
            }
            else if (contador_o == 3) {
                printf("%s\n", mensagem_o);
                return 0;
            }
        }
    }

    // Verificação dos estados nas colunas.
    for (int i = 0; i < 3; i++) {
        contador_x = contador_o = 0;
        for (int j = 0; j < 3; j++) {
            if (jogoVelha[j][i] == 'x') {
                contador_x++;
            }
            else if (jogoVelha[j][i] == 'o') {
                contador_o++;
            }

            if (contador_x == 3) {
                printf("%s\n", mensagem_x);
                return 0;
            }
            else if (contador_o == 3) {
                printf("%s\n", mensagem_o);
                return 0;
            }

        }
    }

    // Verificação dos estados nas diagonais
    if (jogoVelha[0][0] == 'x' && jogoVelha[1][1] == 'x' && jogoVelha[2][2] == 'x') {
        printf("%s\n", mensagem_x);
        return 0;
    }
    else if (jogoVelha[2][0] == 'x' && jogoVelha[1][1] == 'x' && jogoVelha[0][2] == 'x') {
        printf("%s\n", mensagem_x);
        return 0;
    }
    else if (jogoVelha[0][0] == 'o' && jogoVelha[1][1] == 'o' && jogoVelha[2][2] == 'o') {
        printf("%s\n", mensagem_o);
        return 0;
    }
    else if (jogoVelha[2][0] == 'o' && jogoVelha[1][1] == 'o' && jogoVelha[0][2] == 'o') {
        printf("%s\n", mensagem_o);
        return 0;
    }

    // Verificação se esta em jogo
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (jogoVelha[i][j] == '-') {
                printf("em jogo\n");
                return 0;            
            }
        }
    }

    // Se não deu certo até aqui, e porque deu empate.
    printf("%s\n", mensagem_empate);
    return 0;
}