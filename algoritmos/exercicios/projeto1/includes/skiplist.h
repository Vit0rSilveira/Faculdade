#ifndef SKIPLIST_H
#define SKIPLIST_H


/**
 * @brief Define o nível máximo que a estrutura terá, fica a critério de quem
 * usará a estrutura escolher esse valor.
 * 
 */
#define NIVEL_MAX 20

enum booleano {FALSO, VERDADEIRO};

typedef struct skiplist dicionario_t;

typedef int (comparar_t)(void *, void *);
typedef void (free_t)(void *);
typedef void (imprimir_t)(void *);


/**
 * @brief Cria a estrutura skiplist (genérica) e também
 * cria o Header da estrutura. Neste projeto a estrutura é usada como dicionário.
 * 
 * @return dicionario_t*  Retorna a estrutura criada com seu Header.
 */
dicionario_t *criar ();

/**
 * @brief Insere um elemento na estrutura, a inserção é feita de maneira
 * ordenada.
 * 
 * @param sk Estrutura que vai receber o elemento.
 * @param elem Elemento Genérico
 * @param comparar Função de Comparação, é necessário seu uso, devido a
 * estrutura de dados ser genérica.
 * @return int Retorna 1 se a inserção foi feita e zero caso não.
 */
int inserir (dicionario_t *sk, void *elem, comparar_t *comparar);

/**
 * @brief Remove um elemento da estrutura e desaloca a memória que o elemento
 * removido gastou
 * 
 * @param sk Estrutura com os elementos.
 * @param elem Elemento a ser removido, este elemento é a chave do dicionário.
 * @param comparar Função de comparação para saber se o elemento está no
 * dicionário.
 * @param free_fun Função que desaloca a memória usada pelo elemento removido.
 * @return int Retorna 1 se a remoção foi feita e zero caso não.
 */
int remover (dicionario_t *sk, char *elem, comparar_t *comparar, free_t *free_fun);

/**
 * @brief Altera o valor de elemento da estrutura.
 * 
 * @param sk Estrutura com os elementos.
 * @param elem  Elemento a ser alterado.
 * @param comparar Função que compara se o elemento a ser alterado existe na
 * estrutura.
 * @param free_fun Função que desaloca a memória do elemento alterado, isso pois
 * esta função de alteração, insere o elemento recebido como parametro no lugar
 * do antigo elemento.
 * @return int Retorna 1 se a alteração foi feita e zero caso não.
 */
int alterar (dicionario_t *sk, void *elem, comparar_t *comparar, free_t *free_fun);

/**
 * @brief Imprime um elemento desejado pelo usuário.
 * 
 * @param sk Estrutura com os elementos.
 * @param c Elemento a ser impresso.
 * @param comparar Função que compara o elemento com os dados da estrutura, caso
 * for igual, e feita a impressão.
 * @param imprimir Função usada para imprimir o elemento requerido para a
 * impressão
 * @return int Retorna 1 se a impressão foi feita e zero caso não.
 */
int imprimir (dicionario_t *sk, char *c, comparar_t *comparar, imprimir_t *imprimir);

/**
 * @brief Busca um elemento desejado pelo usuário, caso encontrado, esse 
 * elemento é impresso.
 * 
 * @param sk Estrutura com os elementos.
 * @param c Elemento a ser buscado.
 * @param comparar Função que compara o elemento com os dados da estrutura, caso
 * for igual, e feita a impressão.
 * @param imprimir Função usada para imprimir o elemento caso exista
 * @return int Retorna 1 se encontou o elmento e zero caso não.
 */
int buscar(dicionario_t *sk, char *c, comparar_t *comparar, imprimir_t *imprimir);

/**
 * @brief Destrói a estrutura e libera toda a memória alocada.
 * 
 * @param sk Estrutura a ser destruída
 * @param free_fun Função que desaloca a memória alocada pelos elementos da
 * estrutura.
 */
void destruir (dicionario_t *sk, free_t *free_fun);

#endif