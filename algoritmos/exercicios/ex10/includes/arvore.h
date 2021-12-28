#ifndef AB_H
#define AB_H

typedef struct arvore arvore_t;
typedef struct no no_t;

struct arvore {
    no_t *raiz;
};

void print2D(no_t *root);

/**
 * @brief Cria a estrutura de árvore.
 * 
 * @return arvore_t 
 */
arvore_t *criar();

/**
 * @brief Verifica se a árvore está vazia.
 * 
 * @param a 
 * @return int 
 */
int esta_vazia(arvore_t *a);

/**
 * @brief Finaliza a árvore, por ser uma função recursiva, é necessário tem um
 * caso base para não ter stackoverflow.
 * 
 * @param raiz 
 */
void finalizar(no_t *raiz);

/**
 * @brief Imprime toda a árvore, por convenção mostrar sempre começo pela
 * esquerda.
 * 
 * @param raiz 
 */
void imprimir(no_t *raiz);

/**
 * @brief Retorna o tamanho da altura da árvore.
 * 
 * @param raiz 
 * @return int 
 */
int altura(no_t *raiz);

/**
 * @brief Procura se tem um elemento na árvore.
 * 
 * @param raiz 
 * @param x 
 * @return no_t* 
 */
no_t *busca(no_t *raiz, int x);

/**
 * @brief Função de inserção de nó na árvore, por ser uma função recursiva
 * ela recebe o nó raiz como parâmetro e não a árvore.
 * 
 * @param raiz Nó da árvore, como este nó poderá modificado, é preciso ser 
 * ponteiro de ponteiro.
 * @param id 
 * @param valor 
 * @param idEsq 
 * @param idDir 
 */
void inserir_no(no_t **raiz, int id, int valor, int idEsq, int idDir);

/**
 * @brief Função verificar se a soma dos nós filhos de uma árvore resulta no
 * valor do nó pai deles.
 * 
 * @param raiz 
 * @return int 
 */
void soma_nos_filhos(const no_t *raiz, int *i);
#endif