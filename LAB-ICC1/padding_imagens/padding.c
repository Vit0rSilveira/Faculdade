/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>


void paddingImagem(int **imagem, int borda, int altura, int largura);
void printarMatriz(int **matriz, int altura, int largura);
void desalocar(int **matriz, int altura, int largura);


int main() {
    int altura, largura;
    scanf("%d %d", &largura, &altura);

    int **imagem = (int **)malloc(altura * sizeof(int*));
    for(int i = 0; i < altura; i++)
        imagem[i] = (int *)malloc(largura * sizeof(int));

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            scanf("%d", &imagem[i][j]);
        }
    }

    int borda;
    scanf("%d", &borda);
    
    paddingImagem(imagem, borda, altura, largura);

    printf("\n");
    
    printarMatriz(imagem, altura, largura);
    
    desalocar(imagem, altura, largura);

    return 0;
}

void printarMatriz(int **matriz, int altura, int largura) {
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void desalocar(int **matriz, int altura, int largura){
    for(int i = 0; i < altura; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void paddingImagem(int **imagem, int borda, int altura, int largura) {
    int novaAltura = altura + 2 * borda;
    int novaLargura = largura + 2 * borda;

    int **padding = (int **)malloc(novaAltura * sizeof(int *));
    for (int i = 0; i < novaAltura; i++)
        padding[i] = (int *)calloc(novaLargura, sizeof(int));

    for (int i = borda; i < novaAltura - borda; i++) {
        for (int j = borda; j < novaLargura - borda; j++) {
            padding[i][j] = imagem[i - borda][j - borda];
        }
    }

    printarMatriz(padding, novaAltura, novaLargura);

    desalocar(padding, novaAltura, novaLargura);
}
