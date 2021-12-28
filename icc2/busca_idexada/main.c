/**
 * @file main.c
 * @author Vitor da Silveira Paula Nº 10689651
 * @brief Busca indexada.
 * SCC0201 - Introdução à Ciência da Computação 2.
 * @version last version.
 * @date 11 de Dezembro.
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "lista.h"

enum commands {FINISH, UPDATE_LIST, UPDATE_ARRAY, SEARCH_LIST};


void update_list(list_t *l);
index_t *create_array();
char *read_word();
void print_qtd_elems(index_t *array);
void free_memory(list_t *l,index_t *array);


int main(int argc, char *argv[]) {
    list_t *l = create();
    index_t *arrayIndex = create_array();   
    bool updated = false;

    while (!feof(stdin)) {

        int command = 0;
        scanf(" %d", &command);

        if (command == FINISH) {
            free_memory(l, arrayIndex);
            break;
        }
        else if (command == UPDATE_LIST) {
            update_list(l);
            print_list(l, 3);
            updated = false;
        }
        else if (command == UPDATE_ARRAY) {
            update_array_index(l, arrayIndex);
            print_qtd_elems(arrayIndex);
            updated = true;
        }
        else {
            char *word = read_word(stdin);
            if (!updated) {
                printf("Vetor de indices nao atualizado.\n");
                free (word);
                continue;
            }

            int i = search_list(l, arrayIndex, word);
            if (i < 0)
                printf("Palavra nao existe na lista.\n");
            else
                printf("%d\n", i);

            free (word);
        }

    }

    return EXIT_SUCCESS;
}

/**
 * @brief This funcition open the file and reads the words in the file and
 * saves the words readed in the list.
 * 
 * @param l 
 */
void update_list(list_t *l) {
    char *fileName = read_word(stdin);
    FILE *f = fopen(fileName, "r");

    if (!f) {
        printf("Erro ao abrir o arquivo\n");
        free(fileName);
        return;
    }
    
    while (!feof(f)) {
        char *word = read_word(f);
        push_node_list(l, word);
    }
    fclose(f);
    free(fileName);
}

/**
 * @brief Create a array object and inicializes the itens of the array.
 * 
 * @return index_t* 
 */
index_t *create_array() {
    index_t *array = malloc(26 * sizeof(index_t));

    for (int i = 0; i < 26; i++) {
        array[i].firstChar = malloc(2 * sizeof(char));

        int j = 0;
        array[i].firstChar[j] = 'a' + i;
        array[i].firstChar[j + 1] = '\0';

        array[i].address = NULL;
    }

    return array;
}

/**
 * @brief Read a word and saves in the heap memory.
 * 
 * @param file 
 * @return char* It's necessary desalloc the memory.
 */
char *read_word(FILE *file) {
    char *name = NULL;
    char c = '\0';
    int cout = 0;
    
    
    while ((c = fgetc(file)) == '\r' || c == '\n');
    if (c != EOF)
        ungetc(c, file);
    
    do {
        c = fgetc(file);

        name = realloc(name, ++cout * sizeof(char));
        name[cout - 1] = c;

    } while (c != '\r' && c != '\n' && c != EOF);
    name[cout - 1] = '\0';

    return name;
}

/**
 * @brief Print the amount elements in the array.
 * 
 * @param array 
 */
void print_qtd_elems(index_t *array) {
    int count = 0;
    for (int i = 0; i < 26; i++)
        if (array[i].address != NULL)
            count++;

    printf("%d\n", count);
}

void free_memory(list_t *l,index_t *array) {
    for (int i = 0; i < 26; i++)
        free(array[i].firstChar);
    free(array);

    delete_list(l);
}