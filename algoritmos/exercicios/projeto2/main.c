#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treap.h"


char *ler_string();
void insercao(arvore_t *a);
void impressao(arvore_t *a);
void remocao(arvore_t *a);
void busca(arvore_t *a);



int main(int argc, char *argv[]) {
    int qtdLinhas;
    scanf(" %d", &qtdLinhas);

    arvore_t *a = criar_treap();

    for (int i = 0; i < qtdLinhas; i++) {
        char *comando = ler_string();

        if (!strcmp(comando, "insercao"))
            insercao(a);
        else if (!strcmp(comando, "impressao"))
            impressao(a);
        else if (!strcmp(comando, "remocao"))
            remocao(a);
        else
            busca(a);


        free(comando);
    }
    imprimir_treap(a);

    deletar_treap(a);


    return EXIT_SUCCESS;
}

/**
 * @brief Verifica se um caracterer é fim de linha.
 * 
 * @param c 
 * @return int 
 */
int fim_linha(char c) {
    if (c == '\n' || c == '\r')
        return 1;
    
    return 0;
}

/**
 * @brief Lê uma string e aloca sua memória dinâmicamente.
 * 
 * @return char* Necessário quem chamar essa função desalocar a memória
 * utilizada.
 */
char *ler_string() {
    char *comando = NULL;
    char c = '\0';
    int i = 0;

    while (fim_linha(c = getchar()) || c == ' ');
    if (c != EOF)
        ungetc(c, stdin);

    do{
        c = getchar();

        comando = realloc(comando, ++i * sizeof(char));
        comando[i - 1] = c;
    } while (c != ' ' && !fim_linha(c) && c != EOF);
    comando[i - 1] = '\0';

    return comando;
}

void impressao(arvore_t *a) {
    char *tipo = ler_string();

    if (!strcmp(tipo, "ordem"))
        impressao_em_ordem(a);
    else if (!strcmp(tipo, "posordem"))
        impressao_pos_ordem(a);
    else if (!strcmp(tipo, "preordem"))
        impressao_pre_ordem(a);
    else
        impressao_em_largura(a);

    free(tipo);
}

void insercao(arvore_t *a) {
    int chave, prior;
    scanf(" %d %d", &chave, &prior);

    // Caso não der para inserir, é porque o elemento já existe.
    if(!inserir_treap(a, chave, prior))
        printf("Elemento ja existente\n");

}

void remocao(arvore_t *a) {
    int chave;
    scanf(" %d", &chave);

    if(!remover_treap(a, chave))
        printf("Chave nao localizada\n");
}

void busca(arvore_t *a) {
    int chave;
    scanf("%d", &chave);

    int retorno = buscar_treap(a, chave);

    printf("%d\n", retorno);
}