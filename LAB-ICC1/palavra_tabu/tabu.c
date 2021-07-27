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


char *receberFrase();
int quantificar(char tabu[], char *frase);
char *remover(char tabu[], char *frase, int quantidade);


int main() {
    char tabu[21];
    scanf("%s", tabu);
    
    char *frase = receberFrase();

    int qtdTabu = quantificar(tabu, frase);

    char *novaFrase = remover(tabu, frase, qtdTabu);

    printf("A palavra tabu foi encontrada %d vezes\n", qtdTabu);
    printf("Frase: %s\n", novaFrase);

    free(frase);
    free(novaFrase);

    return 0;
}

char *receberFrase() {
    char *frase = NULL;
    char c = '\0';
    int nCaractere = 0;

    while((c = getchar()) == '\n');
    if (c != EOF)
        ungetc(c, stdin);

    do {
        c = getchar();

        char *tmp = (char *)realloc(frase, (++nCaractere) * sizeof(char));
        if (tmp == NULL) {
            printf("Não foi possível fazer a alocação\n");
            free(frase);
            exit(0);
        }
        frase = tmp;
        
        frase[nCaractere - 1] = c;

    } while (c != '$');
    frase[nCaractere - 1] = '\0';

    return frase;
}

int quantificar(char tabu[], char *frase) {
    int tamanhoTabu = strlen(tabu);
    int tamanhoFrase = strlen(frase);
    
    int qtdTabu = 0;
    for (int i = 0; i < (tamanhoFrase - tamanhoTabu + 1); i++) {
        if (strncmp(frase + i, tabu, tamanhoTabu) == 0)
            qtdTabu++;
    }

    return qtdTabu;
}

char *remover(char tabu[], char *frase, int quantidade) {
    int tamanhoNfrase = strlen(frase) - quantidade * strlen(tabu) + 1;
    char *novaFrase = (char *)malloc(tamanhoNfrase * sizeof(char));

    for (int i = 0, j = 0; i < strlen(frase);) {
        if (strncmp(frase + i, tabu, strlen(tabu)) == 0)
            i += strlen(tabu);
        else
            novaFrase[j++] = frase[i++];
    }
    novaFrase[tamanhoNfrase - 1] = '\0';

    return novaFrase;
}
