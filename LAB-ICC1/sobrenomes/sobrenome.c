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


char ***receberNomes (int *qtdNome, int **qtdPalavrasNome);
void printarMudanca (char ***nomes, int qtdNome, int *qtdPalavrasNome);
void desalocarMemoria (char ***nomes, int qtdNome, int *qtdPalavrasNome);


int main() {
    char ***nomes;
    int qtdNome, *qtdPalavrasNome;
    nomes = receberNomes(&qtdNome, &qtdPalavrasNome);

    printarMudanca(nomes, qtdNome, qtdPalavrasNome);

    desalocarMemoria(nomes, qtdNome, qtdPalavrasNome);   

    return 0;
}

char ***receberNomes(int *qtdNome, int **qtdPalavrasNome) {
    char ***receberNomes = NULL;
    char caractere = '\0';
    int qtdCaractere = 0, qtdPalavras = 0, qtdNomes = 0;
    *qtdPalavrasNome = NULL;

    do {
        receberNomes = realloc(receberNomes, ++qtdNomes * sizeof(char **));
        *qtdPalavrasNome = realloc(*qtdPalavrasNome, qtdNomes * sizeof(int));
        qtdPalavras = 0;
        receberNomes[qtdNomes - 1] = NULL;
        do {
            receberNomes[qtdNomes - 1] = realloc(receberNomes[qtdNomes - 1], ++qtdPalavras * sizeof(char *));
            qtdCaractere = 0;
            receberNomes[qtdNomes - 1][qtdPalavras - 1] = NULL;
            do {
                caractere = getchar();

                receberNomes[qtdNomes - 1][qtdPalavras - 1] = realloc(receberNomes[qtdNomes - 1][qtdPalavras - 1], ++qtdCaractere * sizeof(char));
                receberNomes[qtdNomes - 1][qtdPalavras - 1][qtdCaractere - 1] = caractere;

            } while(caractere != ' '  && caractere != '\n' && caractere != '$');

            receberNomes[qtdNomes - 1][qtdPalavras - 1][qtdCaractere - 1] = '\0';

        } while(caractere != '\n' && caractere != '$');
        (*qtdPalavrasNome)[qtdNomes - 1]= qtdPalavras;
    
    } while(caractere != '$' && caractere != EOF);

    *qtdNome = qtdNomes;
    return receberNomes;
}

void printarMudanca(char ***nomes, int qtdNome, int *qtdPalavrasNome) {
     for (int i = 0; i < qtdNome; i++) {
        for (int j = 0; j < (qtdPalavrasNome)[i]; j++) {
            printf("%s ", nomes[i][j]);
        }
        if(i % 2 == 1)
            printf("%s", nomes[i - 1][qtdPalavrasNome[i - 1] - 1]);
        printf("\n");
    }
}

void desalocarMemoria (char ***nomes, int qtdNome, int *qtdPalavrasNome) {
    for (int i = 0; i < qtdNome; i++) {
        for (int j = 0; j < (qtdPalavrasNome)[i]; j++) {
            free(nomes[i][j]);
        }
        free(nomes[i]);
    }
    free(nomes);

    free(qtdPalavrasNome);
}