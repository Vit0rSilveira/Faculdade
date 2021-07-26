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


#define VIVA 'x'
#define MORTA '.'


typedef struct {
    int linhas;
    int colunas;
    int interacoes;
    char tipo;
    char **tabuleiro;
} game_t;


void testarValidade(game_t game);
char **receberMatriz(game_t game);
void simular(game_t game);
void desalocar(game_t game);
void msleep(long msec);


int main() {
    game_t game;
    scanf("%d %d %d", &game.linhas, &game.colunas, &game.interacoes);
    scanf(" %c", &game.tipo);

    testarValidade(game);

    game.tabuleiro = receberMatriz(game);

    for (int i = 0; i < game.interacoes; i++) {
        simular(game);
        for (int i = 0; i < game.linhas; i++) {
            for (int j = 0; j < game.colunas; j++) {
                if (game.tabuleiro[i][j] == VIVA)
                    printf("\033[93m%c", game.tabuleiro[i][j]);
                else if (game.tabuleiro[i][j] == MORTA)
                    printf("\033[0m%c", game.tabuleiro[i][j]);
            }
        printf("\n");
        }
        msleep(100);
        system("clear");
    }
        
    desalocar(game);
    
    return 0;
}

int calcularVivasMoore(int linhas, int colunas, char copia[linhas][colunas], int i, int j) {
    int cima = i - 1 < 0 ? linhas - 1 : i - 1;
    int baixo = (i + 1) % linhas;
    int frente = (j + 1) % colunas;
    int atras = j - 1 < 0 ? colunas - 1 : j - 1;

    int qtdVivos = 0;
    if(copia[i][atras] == VIVA)
        qtdVivos++;
    if(copia[i][frente] == VIVA)
        qtdVivos++;
    if (copia[cima][j] == VIVA)
        qtdVivos++;
    if (copia[baixo][j] == VIVA)
        qtdVivos++;
    if (copia[cima][frente] == VIVA)
        qtdVivos++;
    if (copia[baixo][frente] == VIVA)
        qtdVivos++;
    if (copia[cima][atras] == VIVA)
        qtdVivos++;
    if (copia[baixo][atras] == VIVA)
        qtdVivos++;

    return qtdVivos;
}

int calcularVivasNeumann(int linhas, int colunas, char copia[linhas][colunas], int i, int j) {
    int cima = i - 1 < 0 ? linhas - 1 : i - 1;
    int baixo = (i + 1) % linhas;
    int frente = (j + 1) % colunas;
    int atras = j - 1 < 0 ? colunas - 1 : j - 1;

    int cimaCima = cima - 1 < 0 ? linhas - 1 : cima - 1;
    int baixoBaixo = (baixo + 1) % linhas;
    int frenteFrente = (frente + 1) % colunas;
    int atrasAtras = atras - 1 < 0 ? colunas - 1 : atras - 1;
    
    int qtdVivos = 0;
    if (copia[cima][j] == VIVA)
        qtdVivos++;
    if (copia[cimaCima][j] == VIVA)
        qtdVivos++;
    if (copia[baixo][j] == VIVA)
        qtdVivos++;
    if (copia[baixoBaixo][j] == VIVA)
        qtdVivos++;
    if (copia[i][frente] == VIVA)
        qtdVivos++;
    if (copia[i][frenteFrente] == VIVA)
        qtdVivos++;
    if (copia[i][atras] == VIVA)
        qtdVivos++;
    if (copia[i][atrasAtras] == VIVA)
        qtdVivos++;

    return qtdVivos;
}

void testarValidade(game_t game) {
    if (game.linhas <= 0 || game.colunas <= 0 || game.interacoes <= 0) {
        printf("Dados de entrada apresentam erro.\n");
        exit (0);
    }
    else if (game.tipo != 'M' && game.tipo != 'N') {
        printf("Dados de entrada apresentam erro.\n");
        exit (0);
    }
}

char **receberMatriz(game_t game) {
    char **matriz = (char **)malloc(game.linhas * sizeof(char *));
    for (int i = 0; i < game.linhas; i++) {
        matriz[i] = (char *)malloc(game.colunas * sizeof(char));
    }

    for (int i = 0; i < game.linhas; i++) {
        for (int j = 0; j < game.colunas; j++) {
            scanf(" %c ", &matriz[i][j]);
        }
    }
    return matriz;
}

void simular(game_t game) {
    char copia[game.linhas][game.colunas];
    for (int i = 0; i < game.linhas; i++) {
        for (int j = 0; j < game.colunas; j++) {
            copia[i][j] = game.tabuleiro[i][j];
        }
    }

    for (int i = 0; i < game.linhas; i++) {
        for (int j = 0; j < game.colunas; j++) {
            int qtdVivos;
            if (game.tipo == 'M') 
                qtdVivos = calcularVivasMoore(game.linhas, game.colunas, copia, i, j);
            else
                qtdVivos = calcularVivasNeumann(game.linhas, game.colunas, copia, i, j);

            if (copia[i][j] == VIVA && (qtdVivos < 2 || qtdVivos > 3))
                game.tabuleiro[i][j] = MORTA;
            else if (copia[i][j] == MORTA && qtdVivos == 3)
                game.tabuleiro[i][j] = VIVA;
        }
    }
}

void desalocar(game_t game) {
    for (int i = 0; i < game.linhas; i++)
        free(game.tabuleiro[i]);
    free(game.tabuleiro);
}

void msleep(long msec){
    struct timespec ts;

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    nanosleep(&ts, &ts);
}