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
#include <string.h>
#include <stdbool.h>


typedef enum {
    DIRETO, 
    INDIRETO,
    FALSO
} comandos_t;


char *lerFrase();
int verificarPalindrimo(char *mensagem, int inicio, int tamMensagem, bool direto);


int main() {
    char *mensagem;
    mensagem = lerFrase();

    int inicio = 0;
    int tamMensagem = strlen(mensagem) - 1;
    bool direto = true;

    int solucao = verificarPalindrimo(mensagem, inicio, tamMensagem, direto);

    if (solucao == DIRETO)
        printf("Palindromo direto\n");
    else if (solucao == INDIRETO)
        printf("Palindromo indireto\n");
    else
        printf("Nao eh um palindromo\n");

    free(mensagem);

    return 0;
}

char *lerFrase() {
    char *mensagem = NULL;
    int qtdCaractere = 0;
    char caractere;

    do {
        caractere = getchar();
        caractere = tolower(caractere);

        if (!isalnum(caractere) && caractere !=  ' ' && caractere != '/')
            continue;

        mensagem = realloc(mensagem, ++qtdCaractere * sizeof(char));
        mensagem[qtdCaractere - 1] = caractere;

    } while(caractere != '\n');
    mensagem = realloc(mensagem, ++qtdCaractere * sizeof(char));
    mensagem[qtdCaractere - 1] = '\0';

    return mensagem;
}

/**
 * @brief Função que verifica se e palindrimo e qual o tipo.
 * 
 * @param mensagem Frase a ser analisada.
 * @param inicio Primeiro caractere da frase.
 * @param tamMensagem indice do ultimo caractere da frase.
 * @param direto Booleana que faz o controle se é palindrono direto ou indireto.
 * @return Se a frase for palindromo retorna o tipo ou se não, retorna que não é.
 */
int verificarPalindrimo(char *mensagem, int inicio, int tamMensagem, bool direto) {
    if (inicio >= tamMensagem && direto == false)
        return INDIRETO;
    if (inicio >= tamMensagem && direto == true)
        return DIRETO;

    if (mensagem[inicio] != mensagem[tamMensagem]) {
        direto = false;

        if (mensagem[inicio] == ' ' || mensagem[inicio] == '/') 
            return verificarPalindrimo(mensagem, inicio + 1, tamMensagem, direto);
        else if (mensagem[tamMensagem] == ' ' || mensagem[tamMensagem] == '/') 
            return verificarPalindrimo(mensagem, inicio, tamMensagem - 1, direto);
    }

    if (mensagem[inicio] == mensagem[tamMensagem])
        return verificarPalindrimo(mensagem, inicio + 1, tamMensagem - 1, direto);

    return FALSO;
}
