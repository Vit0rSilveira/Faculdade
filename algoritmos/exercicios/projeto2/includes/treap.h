#ifndef TREAP_H
#define TREAP_H

typedef struct no no_t;
typedef struct arvore arvore_t;


/**
 * @brief Cria a árvore, e retorna.
 * 
 * @return arvore_t* 
 */
arvore_t *criar_treap();

/**
 * @brief Deleta a árvore e libera a memória de todas as subárvores.
 * 
 * @param a 
 */
void deletar_treap(arvore_t *a);

/**
 * @brief Insere um elemento na treap de forma que a treap fique balanceada.
 * 
 * @param a 
 * @param info 
 * @param prior 
 * @return int
 */
int inserir_treap(arvore_t *a, int info, int prior);

/**
 * @brief Remove um elemento caso exista na treap
 * 
 * @param a 
 * @param info 
 * @return int 
 */
int remover_treap(arvore_t *a, int info);

/**
 * @brief Busca se um elemento está na árvore.
 * 
 * @param a 
 * @param info 
 * @return int retorna 1 caso exista e zero caso não.
 */
int buscar_treap(arvore_t *a, int info);

/**
 * @brief Imprime a árvore
 * 
 * @param a 
 */
void imprimir_treap(arvore_t *a);

/**
 * @brief Imprime os nós da árvore em ordem.
 * 
 * @param a 
 */
void impressao_em_ordem(arvore_t *a);

/**
 * @brief Imprime os nós da árvore em pré ordem.
 * 
 * @param a 
 */
void impressao_pre_ordem(arvore_t *a);

/**
 * @brief Imprime os nós da árvore em pós ordem.
 * 
 * @param a 
 */
void impressao_pos_ordem(arvore_t *a);

/**
 * @brief Imprime a árvore em largura, ou seja, imprime o nó e seus filhos a
 * esquerda e a direita.
 * 
 * @param a 
 */
void impressao_em_largura(arvore_t *a);


#endif