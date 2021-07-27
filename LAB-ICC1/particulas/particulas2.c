/*---------------------------------------------------------------------- 
                        Universidade de São Paulo
        Instituto de Ciências Matemáticas e de Computação - ICMC
            Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                    Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define AGUA '~'
#define AREIA '#'
#define CIMENTO '@'
#define AR ' '
#define LINHAMAX 32
#define COLUNAMAX 64


char particulas[LINHAMAX][COLUNAMAX];

void atualizacaoFisica ();
void msleep(long msec);


int main () {
    for (int i = 0; i < LINHAMAX; i++) {
        for (int j = 0; j < COLUNAMAX; j++) {
            particulas[i][j] = ' ';
        }
    }

    int numeroFrames, frame, x, y;
    char novaParticula;

    scanf("%d", &numeroFrames);
    
    int rodada = 0;
    while (rodada < numeroFrames) {
        int retorno = scanf(" %d: %d %d %c", &frame, &x, &y, &novaParticula);
        
        // Se não há mais partículas a serem criadas, continue até o final da simulação.
        if (retorno == EOF) {
            frame = numeroFrames;
        }

        while (rodada < frame) {
            printf("frame: %d\n", rodada + 1);
            for (int i = 0; i < LINHAMAX; i++) {
                for (int j = 0; j < COLUNAMAX; j++) {

                    switch(particulas[i][j]) {
                        case AREIA:
                            printf("\033[93m%c", particulas[i][j]);
                            break;
                        case AGUA:
                            printf("\033[94m%c", particulas[i][j]);
                            break;
                        case CIMENTO:
                            printf("\033[0m%c", particulas[i][j]);
                            break;
                        default:
                            printf("\033[0m%c", particulas[i][j]);
                            break;
                    }
                }
                printf("\n");
            }

            atualizacaoFisica();
            rodada++;
            msleep(100);
            system("clear");
        }
        // Se há uma particula a ser criada, crie ela.
        if (retorno != EOF) {
            particulas[y][x] = novaParticula;
        }
    }

    printf("\x1b[0m");
    return 0;
}

void substituicao(char *a, char *b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void atualizacaoFisica() {
    char copiaParticulas[LINHAMAX][COLUNAMAX];

    for (int i = 0; i < LINHAMAX; i++) {
        for (int j = 0; j < COLUNAMAX; j++) {
            copiaParticulas[i][j] = particulas[i][j];
        }
    }

    for (int i = 0; i < LINHAMAX; i++) {
        for (int j = 0; j < COLUNAMAX; j++) {

            if (particulas[i][j] == AGUA) {
                if (i + 1 < LINHAMAX && particulas[i + 1][j] == AR)
                    substituicao(&copiaParticulas[i][j], &copiaParticulas[i + 1][j]);
                else if (i + 1 < LINHAMAX && j - 1 >= 0 && particulas[i + 1][j - 1] == AR)
                    substituicao(&copiaParticulas[i][j], &copiaParticulas[i + 1][j - 1]);
                else if (i + 1 < LINHAMAX && j + 1 < COLUNAMAX && particulas[i + 1][j + 1] == AR)
                    substituicao(&copiaParticulas[i][j], &copiaParticulas[i + 1][j + 1]);
                else if (j - 1 >= 0 && particulas[i][j - 1] == AR)
                    substituicao(&copiaParticulas[i][j], &copiaParticulas[i][j - 1]);
                else if (j + 1 < COLUNAMAX && particulas[i][j + 1] == AR)
                    substituicao(&copiaParticulas[i][j], &copiaParticulas[i][j + 1]);
            }
            else if (particulas[i][j] == AREIA) {
                if (i + 1 < LINHAMAX && (particulas[i + 1][j] == AR || particulas[i + 1][j] == AGUA))
                    substituicao(&copiaParticulas[i][j], &copiaParticulas[i + 1][j]);
                else if (i + 1 < LINHAMAX && j - 1 >= 0  && (particulas[i + 1][j - 1] == AR || particulas[i + 1][j - 1] == AGUA))
                    substituicao(&copiaParticulas[i][j], &copiaParticulas[i + 1][j - 1]);
                else if (i + 1 < LINHAMAX && j + 1 < COLUNAMAX && (particulas[i + 1][j + 1] == AR || particulas[i + 1][j + 1] == AGUA))
                    substituicao(&copiaParticulas[i][j], &copiaParticulas[i + 1][j + 1]);
            }
        }
    }

    for (int i = 0; i < LINHAMAX; i++) {
        for (int j = 0; j < COLUNAMAX; j++) {
            particulas[i][j] = copiaParticulas[i][j];
        }
    }

}

void msleep(long msec){
    struct timespec ts;

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    nanosleep(&ts, &ts);
}
