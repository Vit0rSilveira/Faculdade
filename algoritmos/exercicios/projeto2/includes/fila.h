#ifndef FILA_H
#define FILA_H

typedef struct fila fila_t;

/**
 * @brief Cria uma fila
 * 
 * @return fila_t* 
 */
fila_t *criar_fila();

/**
 * @brief cria um nó e insere este na fila.
 * 
 * @param l 
 * @param info 
 * @param prior 
 */
void inserir_fila(fila_t *l, void *info);

/**
 * @brief Libera toda memória alocada pela fila e deleta a mesma.
 * 
 * @param l 
 */
void deletar_fila(fila_t *l);

/**
 * @brief Retorna o tamanho da fila
 * 
 * @param l 
 * @return int 
 */
int esta_vazia(fila_t *l);


/**
 * @brief Remove um elemento da fila.
 * 
 * @param l 
 * @param x 
 * @return int 
 */
void *remover_fila(fila_t *l);


#endif