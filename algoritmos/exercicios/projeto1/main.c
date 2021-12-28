#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "skiplist.h"

#define EH_ESPACO(c) (c == ' ')
#define FIM_LINHA(c) (c == '\r' || c == '\n')

struct dados {
    char *chave;
    char *valor;
};

typedef struct dados dados_t;


char *ler_string(int ehPalavra);
int eh_fim();
int comparar_string(dados_t *x, dados_t *y);
int comparar_caracterer(dados_t *x, char *y);
void mostrar_dados(dados_t *d);
void liberar_dados(dados_t *d);
void inserir_dicionario(dicionario_t *sk);
void alterar_dicionario(dicionario_t *sk);
void remover_dicionario(dicionario_t *sk);
void buscar_dicionario(dicionario_t *sk);
void imprimir_dicionario(dicionario_t *sk);


int main(int argc, char *argv[]) {
    dicionario_t *sk = criar();

    while (!eh_fim()) {
        char *comando = ler_string(VERDADEIRO);

        if (strcmp(comando, "insercao") == 0)
            inserir_dicionario(sk);
        else if (strcmp(comando, "alteracao") == 0)
            alterar_dicionario(sk);
        else if (strcmp(comando, "remocao") == 0)
            remover_dicionario(sk);
        else if (strcmp(comando, "busca") == 0)
            buscar_dicionario(sk);
        else if (strcmp(comando, "impressao") == 0)
            imprimir_dicionario(sk);

        free(comando);
    }

    destruir(sk, (free_t *)liberar_dados);

    return EXIT_SUCCESS;
}

/**
 * @brief Verifica se é o fim do arquivo lido.
 * 
 * @return int 
 */
int eh_fim() {
    char c = getchar();
    if (c != EOF) {
        ungetc(c, stdin);
        return FALSO;
    }

    return VERDADEIRO;
}

/**
 * @brief Função de leitura das informações, sejam os comandos, chaves ou
 * valores do dicionário. As strings são alocadas dinâmicamente na memória.
 * 
 * @param ehPalavra Flag que determina se o que será lido é uma palavra
 * ou uma expressão.
 * @return char* Retorna o ponteiro, o qual aponta para a string alocada.
 */
char *ler_string(int ehPalavra) {
    char *palavra = NULL;
    char c = '\0';
    int tmp = 0;

    while (EH_ESPACO((c = getchar())) || FIM_LINHA(c));

    if (c != EOF)
        ungetc(c, stdin);

    do {
        c = getchar();

        palavra = realloc(palavra, ++tmp * sizeof(char));
        palavra[tmp - 1] = c;

        if (ehPalavra) {
            if (EH_ESPACO(c))
                break;
        }

    } while (!FIM_LINHA(c) && c != EOF);
    palavra[tmp - 1] = '\0';

    return palavra;
}

/**
 * @brief Lê as informações a serem passadas pelo dicionário e chama a função
 * de inserção no dicionário. É importante salientar que é necessário que as
 * informações sejam salvas na memória Heap, pois quando está função acabar, as
 * informações não podem ser desalocadas pela stack.
 * 
 * @param sk Estrutura Dicionário na qual receberá o elemento.
 */
void inserir_dicionario(dicionario_t *sk) {
    dados_t *d = malloc(sizeof(dados_t));
    d->chave = ler_string(VERDADEIRO);
    d->valor = ler_string(FALSO);

    if (!inserir(sk, d, (comparar_t *)comparar_string)) {
        printf("OPERACAO INVALIDA\n");
        liberar_dados(d);
    }
}

/**
 * @brief  Lê as informações a serem passadas pelo dicionário e chama a função
 * de alteração no dicionário. É importante salientar que é necessário que as
 * informações sejam salvas na memória Heap, pois quando está função acabar, as
 * informações não podem ser desalocadas pela stack.
 * 
 * @param sk Estrutura Dicionário na qual receberá o elemento para a alteração.
 */
void alterar_dicionario(dicionario_t *sk) {
    dados_t *d = malloc(sizeof(dados_t));
    d->chave = ler_string(VERDADEIRO);
    d->valor = ler_string(FALSO);

    if (!alterar(sk, d, (comparar_t *)comparar_string, (free_t *)liberar_dados)) {
        printf("OPERACAO INVALIDA\n");
        liberar_dados(d);
    }
}

/**
 * @brief Recebe a chave e chama a função de busca no dicionário.
 * 
 * @param sk Estrutura dicionário a ser passado para a busca.
 */
void buscar_dicionario(dicionario_t *sk) {
    char *chave = ler_string(FALSO);

    if (!buscar(sk, chave, (comparar_t *)comparar_caracterer, (imprimir_t *)mostrar_dados))
        printf("OPERACAO INVALIDA\n");

    free(chave);
}

/**
 * @brief Recebe a chave e chama a função de remoção da estrutura para remover
 * o elemento da estrutura.
 * 
 * 
 * @param sk Estrutura dicionário a ser passado para a remoção.
 */
void remover_dicionario(dicionario_t *sk) {
    char *chave = ler_string(VERDADEIRO);

    if (!remover(sk, chave, (comparar_t *)comparar_caracterer, (free_t *)liberar_dados))
        printf("OPERACAO INVALIDA\n");

    free(chave);
}

/**
 * @brief Função que recebe um caracterer e o salva como string (coloca o \0
 * após esse caracter) e chama a função de imprirmir no dicionário.
 * 
 * @param sk Estrutura dicionário a ser passado para a impressão.
 */
void imprimir_dicionario(dicionario_t *sk) {
    char *ch = ler_string(FALSO);

    if (!imprimir(sk, ch, (comparar_t *)comparar_caracterer, (imprimir_t *)mostrar_dados))
        printf("NAO HA PALAVRAS INICIADAS POR '%s'\n", ch);

    free(ch);
}

// A baixo seguem as funções usadas como ponteito de função no TAD genérico.

/**
 * @brief Compara se a chave de um dado começa com o mesmo caracterer passado.
 * 
 * @param x Estrutura dados, contendo a chave.
 * @param y String com o caracterer a ser comparado.
 * @return int 
 */
int comparar_caracterer(dados_t *x, char *y) {
    return strncmp(x->chave, y, strlen(y));
}

/**
 * @brief Compara se as chaves de duas estruturas são iguais.
 * 
 * @param x Estrutura dados, contendo uma das chaves.
 * @param y Estrutura dados, a outra chave.
 * @return int 
 */
int comparar_string(dados_t *x, dados_t *y) {
    return strcmp(x->chave, y->chave);
}

/**
 * @brief Mostra a chave e o valor do elemento.
 * 
 * @param d Dado com as informações a serem printadas.
 */
void mostrar_dados(dados_t *d) {
    printf("%s %s\n", d->chave, d->valor);
}

/**
 * @brief Função libera a memória alocada para a chave e o valor do dado.
 * 
 * @param d Dado com as informações a serem liberadas.
 */
void liberar_dados(dados_t *d) {
    if (d->valor != NULL)
        free(d->valor);
    if (d->chave != NULL)
        free(d->chave);
    free(d);
}