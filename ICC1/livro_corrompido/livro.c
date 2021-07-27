/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>


char *readString(char delimitador);


int main() {
    int numberLine;
    scanf("%d ", &numberLine);

    const char DELIMITADOR = '\n';

    char *lines[numberLine];
    for (int i = 0; i < numberLine; i++)
        lines[i] = readString(DELIMITADOR);

    int lineValid, indexValid;
    scanf("%d", &lineValid);
    for (int i = 0; i < lineValid; i++) {
        scanf("%d", &indexValid);
        printf("%s\n", lines[indexValid]);
    }

    for (int i = 0; i < numberLine; i++)
        free(lines[i]);
    return 0;

}

char *readString(char delimitador) {
    char *line = NULL;
    char caractere;

    int sizeLine = 0;
    do {
        caractere = getchar();

        line = realloc(line, (sizeLine + 1) * sizeof(char));
        if (line == NULL) {
            printf("Erro na alocação de memória\n");
            exit(0);
        }
        
        line[sizeLine++] = caractere;

    } while (caractere != delimitador && caractere != EOF);

    line[sizeLine - 1] = '\0';

    return line;
}