#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"


struct node {
    int value;
    node_t *left;
    node_t *right;
};

tree_t *creat() {
    tree_t *t = malloc(sizeof(tree_t));
    t->root = NULL;

    return t;
}

void finish_node_tree(node_t *root) {
    if (!root) return;

    finish_node_tree(root->left);
    finish_node_tree(root->right);
    free(root);
}

int is_empty(tree_t *t) {
    return (!t->root);
}

void print_tree(node_t *root) {
    if (root != NULL) {
        printf("%d(", root->value);
        print_tree(root->left);

        printf(",");

        print_tree(root->right);
        printf(")");
    }
    else
        printf("null");
}

int height(node_t *root) {
    if (root == NULL)
        return 0;

    int hLeft = 1 + height(root->left);
    int hRight = 1 + height(root->right);

    if (hLeft > hRight)
        return hLeft;

    return hRight;
}

/**
 * @brief visita-se nó raiz primeiro e depois as subárvores
 * esquerda e direita, nessa ordem
 * 
 * 
 * @param root 
 */
int pre_order(node_t *root) {
    if (root == NULL) return 0;

    printf("%d ", root->value);
    pre_order(root->left);
    pre_order(root->right);

    return 1;
}

/**
 * @brief visita-se subárvore esquerda, nó raiz e subárvore direita, 
 * nessa ordem
 * 
 * @param root 
 */
int in_order(node_t *root) {
    if (root == NULL) return 0;

    in_order(root->left);
    printf("%d ", root->value);
    in_order(root->right);

    return 1;
}

/**
 * @brief visita-se subárvore esquerda, subárvore direita, e, 
 * depois, o nó raiz, nessa ordem
 * 
 * @param root 
 */
int pos_order(node_t *root) {
    if (root == NULL) return 0;

    pos_order(root->left);
    pos_order(root->right);
    printf("%d ", root->value);

    return 1;
}

node_t *search_value(node_t *root, int value) {
    if (!root) 
        return NULL;
    else if (root->value == value)
        return root;
    else if (root->value > value)
        return search_value(root->left, value);
    else
        return search_value(root->right, value);  
    
}

int push_node(node_t **root, int value) {
    if (*root == NULL) {
        *root = malloc(sizeof(node_t));
        (*root)->value = value;
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else if ((*root)->value == value)
        return 0;
    else if ((*root)->value > value)
        return push_node(&(*root)->left, value);
    else
        return push_node(&(*root)->right, value);
    
    return 1;
}

int remove_node(node_t **root, int value) {
    if (*root == NULL)
        return 0;
    // Valor do meu nó é maior que quero remover, procurar na esquerda
    else if ((*root)->value > value)
        remove_node(&(*root)->left, value);
    // Valor do meu nó é menor do que quero remover, procurar na direta
    else if ((*root)->value < value)
        remove_node(&(*root)->right, value);
    else {
        if ((*root)->left == NULL && (*root)->right == NULL) {
            free(*root);
            *root = NULL;

            return 1;
        }
        else if ((*root)->left == NULL) {
            node_t *aux = *root;
            *root = (*root)->right;
            free(aux);

            return 1;
        }
        else if ((*root)->right == NULL) {
            node_t *aux = *root;
            *root = (*root)->left;
            free(aux);

            return 1;
        }
        else {
            node_t *aux = (*root)->right;

            while (aux->left != NULL)
                aux = aux->left;

            (*root)->value = aux->value;

            return remove_node(&(*root)->right, aux->value);

            return 1;
        }
    }
    return 1;
}