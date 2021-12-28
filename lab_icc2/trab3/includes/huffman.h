#ifndef HUFFMAN_H
#define HUFFMAN_H


typedef struct tree tree_t;
typedef struct array_compress table_t;


/**
 * @brief Cria a árvore de huffman com base na frequencia estabelecidade pelo
 * vetor
 * 
 * @param array 
 * @return tree* 
 */
tree_t *create_huffman(char *string);

/**
 * @brief Deleta a árvore e todos os nós da mesma. Desalocando toda a memória
 * usada.
 * 
 * @param a 
 */
void delete_huffman(tree_t *a);

/**
 * @brief Printa a árvore com seus espaçamentos.
 * 
 * @param t 
 */
void print_huffman(tree_t *t);


/**
 * @brief Cria o array de compressão, o qual possui o caracterer e o caminho
 * usado pelo mesmo.
 * 
 * @param t 
 * @return compress_t* 
 */
table_t *create_array_compress(tree_t *t);

/**
 * @brief Mostra os caracteres e a compressão deles.
 * 
 * @param c 
 */
void print_compressed(table_t *c);

/**
 * @brief Deleta o vetor de compressão.
 * 
 * @param c 
 */
void delete_array_compress(table_t *c);

/**
 * @brief Comprime a frase e devolve a frase comprimida.
 * 
 * @param c 
 * @param string 
 * @return char* 
 */
char *compress_phrase(table_t *c, char *string);

/**
 * @brief Decodifica a frase por meio da descompressão.
 * 
 * 
 * @param stringCompressed 
 * @param t 
 * @return char* 
 */
char *decompress_phrase(char *stringCompressed, tree_t *t);

/**
 * @brief Cálcula a taxa de compressão com base na frase decodificada
 * e com a frase codificada.
 * 
 * @param string 
 * @param stringCompressed 
 * @return double 
 */
double calc_tax_compress(char *string, char *stringCompressed);

#endif