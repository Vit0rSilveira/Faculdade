/**
 * @file main.c
 * @author Vitor da Silveira Paula Nº 10689651
 * @brief 
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

typedef int elem_t;
typedef struct tree tree_t;
typedef struct image image_t;

struct tree {
    elem_t elem;
    tree_t *son;
};

struct image {
    int line;
    int column;
    elem_t **image;
};

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


image_t receive_image();
void free_memory(image_t *image);
void free_son(tree_t *tree);
void quad_tree(image_t *image, int beginL, int beginC, int endL, int endC, tree_t *son);


int main(int argc, char *argv[]) {
    image_t image = receive_image();
    tree_t tree;

    quad_tree(&image, 0, 0, image.line, image.column, &tree);
    printf("\n");

    free_son(&tree);
    free_memory(&image);

    return EXIT_SUCCESS;
}

/**
 * @brief Allocates the necessary memory for image and receive de image
 * 
 * @return image
 */
image_t receive_image() {
    image_t image;
    scanf(" %d %d", &image.line, &image.column);

    image.image = malloc(image.line * sizeof(elem_t *));
    for(int i = 0; i < image.line; i++)
        image.image[i] = malloc(image.column * sizeof(elem_t));

    for(int i = 0; i < image.line; i++) {
        for(int j = 0; j < image.column; j++)
            scanf(" %d", &image.image[i][j]);
    }
    
    return image;
}

/**
 * @brief Verify if all elements that are inside the delimited perimeter are
 * equals 
 * 
 * @param image 
 * @param beginL 
 * @param beginC 
 * @param endL 
 * @param endC 
 * @return true 
 * @return false 
 */
bool is_equal(elem_t **image, int beginL, int beginC, int endL, int endC) {
    elem_t tmp = image[beginL][beginC];
    bool isEqual = true;

    for(int i = beginL; i < endL; i++) {
        for(int j = beginC; j < endC; j++) {
            if(tmp != image[i][j]) {
                isEqual = false;
                break;
            }
        }
        if(isEqual == false)
            break;
    }
    
    return isEqual;
}

/**
 * @brief Recursive function. If the perimeter's element isn't equals, this
 * function calls itself
 * 
 * @param image 
 * @param beginL 
 * @param beginC 
 * @param endL 
 * @param endC 
 * @param son 
 */
void quad_tree(image_t *image, int beginL, int beginC, int endL, int endC, tree_t *son) {
    if(beginL > endL || beginC > endC) 
        return;

    bool isEqual = is_equal(image->image, beginL, beginC, endL, endC);

    if(isEqual) {
        son->elem = image->image[beginL][beginC];
        printf("%d ", son->elem);
        return;
    }
    else {
        son->elem = -1;
        printf("%d ", son->elem);
        son->son = malloc(4 * sizeof(tree_t));

        for(int i = 0; i < 4; i++) {
            son->son[i].elem = 0;
            son->son[i].son = NULL;
        }

        int mediumL = (beginL + endL) / 2;
        int mediumC = (beginC + endC) / 2;

        quad_tree(image, beginL, beginC, mediumL, mediumC, &son->son[0]);

        quad_tree(image, beginL, mediumC, mediumL, endC,  &son->son[1]);

        quad_tree(image, mediumL, beginC, endL, mediumC, &son->son[2]);

        quad_tree(image, mediumL, mediumC, endL, endC, &son->son[3]);
    }

}

/**
 * @brief Recursive function. If the tree's son isn't NULL. this function calls 
 * itself for the each child of the tree.
 * 
 * @param tree 
 */
void free_son(tree_t *tree) {
    if(tree->son != NULL) {
        free_son(&tree->son[0]);
        free_son(&tree->son[1]);
        free_son(&tree->son[2]);
        free_son(&tree->son[3]);
        free(tree->son);
    }
}

void free_memory(image_t *image) {
    for(int i = 0; i < image->line; i++)
        free(image->image[i]);
    free(image->image);

}