#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "huffman.h"

#define COUNT 10

typedef struct node node_t;
typedef struct frequency freq_t;
typedef struct compress compress_t;


struct frequency {
    node_t **array;
    int size;
};

struct node {
    char c;
    int recurrence;
    node_t *left;
    node_t *right;
};

struct tree {
    node_t *root;
};

struct compress {
    char c;
    char *encoding;
};

struct array_compress {
    compress_t **compress;
    int size;
};

static void swap(node_t **a, node_t **b) {
    node_t *tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * @brief Procura o indice de um caracterer no vetor.
 * 
 * @param c 
 * @param f 
 * @param j 
 * @return int índice do char no vetor, caso não exista, retorna -1.
 */
static int search_index(char c, freq_t *f, int j) {
    for (int i = 0; i < j; i++) {
        if (c == f->array[i]->c)
            return i;
    }

    return -1;
}

void print_array(freq_t *f) {
    for (int i = 0; i < f->size; i++)
        printf("(%c, %d) ", f->array[i]->c, f->array[i]->recurrence);

    printf("\n");
}

freq_t *count_recurrence_node(char *phrase) {
    freq_t *f = malloc(sizeof(freq_t));
    f->array = NULL;
    f->size = 0;

    int j = 0;

    for (int i = 0; i < strlen(phrase); i++) {
        // Procurar o indice do char no vetor de frequencia.
        int k = search_index(phrase[i], f, j);

        /*  Se não existe o char no vetor, realocar espaço para tal
            e adicionar no vetor. */
        if (k == -1) {
            f->array = realloc(f->array, ++j * sizeof(node_t *));
            f->array[j - 1] = malloc(sizeof(node_t));

            f->array[j - 1]->c = phrase[i];
            f->array[j - 1]->recurrence = 1;
            f->array[j - 1]->left = NULL;
            f->array[j - 1]->right = NULL;

            f->size++;
        }
        else
            f->array[k]->recurrence++;

    }

    return f;
}

void min_heap(node_t **v, int father, int size) {

    int son = father * 2 + 1;

    if (son > size) return;

    if (v[son]->recurrence < v[father]->recurrence ||
        (son + 1 <= size && v[son + 1]->recurrence < v[father]->recurrence)) {

        if (son + 1 <= size && v[son + 1]->recurrence < v[son]->recurrence)
            son = son + 1;
            
        swap(&v[father], &v[son]);

        min_heap(v, son, size);
    }

}

/**
 * @brief Monta a min heap do vetor de nós, com base na recorrência.
 * 
 * @param n 
 * @param size 
 */
void build_min_heap(node_t **n, int size) {
    int m = (int)size / 2;

    for (int i = m; i >= 0; i--)
        min_heap(n, i, size);
}

tree_t *create_huffman(char *string) {
    freq_t *f = count_recurrence_node(string);

    build_min_heap(f->array, f->size - 1);

    /*  Após a montagem da min heap, o algoritmo coloca o menor valor no final
        do vetor, e monta a min heap novamente excluindo o ultimo elemento.
        Tendo os dpos menores elementos, no começo e no fim, cria - se um
        novo nó com esses elementos, e esse novo nó, é inserido no vetor.
        Ao fim, o vetor tem apenas um nó, que é a raiz da árvore. */
    for (int i = f->size - 1; i > 0; i--) {
        swap(&f->array[i], &f->array[0]);

        min_heap(f->array, 0, i - 1);

        node_t *new = malloc(sizeof(node_t));
        
        new->c = '\0';
        new->recurrence = f->array[i]->recurrence + f->array[0]->recurrence;
        new->left = f->array[i];
        new->right = f->array[0];

        f->array[0] = new;

        min_heap(f->array, 0, i - 1);
    }

    tree_t *t = malloc(sizeof(tree_t));
    t->root = f->array[0];

    /*  Os nós do vetor de nós, estão na árvore e ela quem é resposável
        pela desalocação de tal memória. */
    free(f->array);
    free(f);

    return t;
}

void delete_nodes(node_t *root) {
    if (root == NULL) return;

    delete_nodes(root->left);
    delete_nodes(root->right);

    free(root);
}

void delete_huffman(tree_t *t) {
    delete_nodes(t->root);
    free(t);
}

void print_tree(node_t *root, int space) {
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print_tree(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("('%c', %d)\n", root->c, root->recurrence);
 
    // Process left child
    print_tree(root->left, space);
}

void print_huffman(tree_t *t) {
   print_tree(t->root, 0);
}

void compress(node_t *root, char **stringCompressed, table_t *c, int h) {
    *stringCompressed = realloc(*stringCompressed, (h + 1) * sizeof(char));

    /*  Se o nó não possui filhos, realocar uma posição para o caracterer na
        tabela, colocar o caracterer e alocar memória para a string comprimida
        e salvar essa string.
    */
    if (root->left == NULL && root->right == NULL) {
        c->compress = realloc(c->compress, ++c->size * sizeof(compress_t *));
        c->compress[c->size - 1] = malloc(sizeof(compress_t));
        c->compress[c->size - 1]->c = root->c;

        c->compress[c->size - 1]->encoding = malloc((h + 1)* sizeof(char));

        (*stringCompressed)[h] = '\0';
        strcpy(c->compress[c->size - 1]->encoding, *stringCompressed);
        return;
    }

    /*  Se possui filhos, chamar a recursão para os filhos, quando for para
        direita, colocar o char '1' na string comprimida, e quando for
        para esquerda, colocar o char '0'.*/
    (*stringCompressed)[h] = '1';
    compress(root->right, stringCompressed, c, h + 1);
    (*stringCompressed)[h] = '0';
    compress(root->left, stringCompressed, c, h + 1);

    (*stringCompressed)[h] = '\0';

}

void print_compressed(table_t *c) {
    printf("\tchar | \tenconding\n");
    for (int i = 0; i < c->size; i++)
        printf("\t%c    | \t%s\n", c->compress[i]->c, c->compress[i]->encoding);
    printf("\n");

}

table_t *create_array_compress(tree_t *t) {
    //  Guardar a compressão, é um auxiliar na criação do mapa.
    char *stringCompressed = NULL;
    table_t *c = malloc(sizeof(table_t));
    c->compress = NULL;
    c->size = 0;

    compress(t->root, &stringCompressed, c, 0);

    free(stringCompressed);

    return c;
}

void delete_array_compress(table_t *c) {
    for (int i = 0; i < c->size; i++) {
        free(c->compress[i]->encoding);
        free(c->compress[i]);
    }
    free(c->compress);
    free(c);
}

char *compress_phrase(table_t *c, char *string) {
    int count = 1;
    char *stringC = malloc(count * sizeof(char));
    stringC[0] = '\0';
    /*  Quando o char da frase for igual ao char do mapa, alocar espaço do
        tamanho do código do char e concatenar esse código na string comprimida.
    */
    for (int i = 0; i < strlen(string); i++) {
        for (int j = 0; j < c->size; j++) {
            if (string[i] == c->compress[j]->c) {
                count += strlen(c->compress[j]->encoding);
                stringC = realloc(stringC, count * sizeof(char));
                stringC[count - 1] = '\0';

                strcat(stringC, c->compress[j]->encoding);
                break;
            }
        }
    }
    stringC = realloc(stringC, (count + 1) * sizeof(char));
    stringC[count] = '\0';

    return stringC;
}

char *decompress_phrase(char *stringCompressed, tree_t *t) {
    char *phrase = NULL;
    int i = 0;
    int tam = 0;

    while (i < strlen(stringCompressed)) {
        node_t *aux = t->root;
        // Percorrer enquanto não for nó folha.
        while (aux->left != NULL && aux->right != NULL) {
            /*  Se o char na string comprimida for igual a '0', ir para nó
                da esquerda.*/
            if (stringCompressed[i] == '0')
                aux = aux->left;
            else
                aux = aux->right;

            i++;
        }
        // Alocar e colocar o char, pois está em um nó folha.
        phrase = realloc(phrase, ++tam * sizeof(char));
        phrase[tam - 1] = aux->c;
    }

    phrase = realloc(phrase, (tam + 1) * sizeof(char));
    phrase[tam] = '\0';

    return phrase;
}

double calc_tax_compress(char *string, char *stringCompressed) {
    return ((double) strlen(stringCompressed) / (strlen(string) * 8));
}