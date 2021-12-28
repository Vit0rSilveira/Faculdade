#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"


void adicionar_arvore(arvore_t *a);

int main(int argc, char *argv[]) {
    arvore_t *a = criar();

    adicionar_arvore(a);
    print2D(a->raiz);
    
    int soma = 1;
    soma_nos_filhos(a->raiz, &soma);
    if (soma)
        printf("VERDADEIRO\n");
    else
        printf("FALSO\n");


    finalizar(a->raiz);
    free(a);

    return EXIT_SUCCESS;
}

/**
 * @brief Função que adiciona os valores na árvore, para isso, a cada iteração
 * ela recebe o id do nó, o valor do nó, e o id dos filhos esquerdo
 * e direito respectivamente. A cada iteração inserido o nó na lista.
 * 
 * @param a 
 */
void adicionar_arvore(arvore_t *a) {
    int tam = 0;
    scanf(" %d", &tam);

    for (int i = 0; i < tam; i++) {
        int id, valor, idEsq, idDir;
        scanf(" %d %d %d %d", &id, &valor, &idEsq, &idDir);

        inserir_no(&a->raiz, id, valor, idEsq, idDir);
    }
}