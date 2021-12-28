#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "lista.h"



list_t *create() {
    list_t *l = malloc(sizeof(list_t));

    l->begin = NULL;
    l->end = NULL;

    return l;
}

void delete_list(list_t *l) {
    if (!l) return;
    node_t *aux = l->begin;

    while (aux != NULL) {
        l->begin = aux->next;
        free(aux->word);
        free(aux);
        aux = l->begin;
    }
    free(l);
}

void print_list(list_t *l, int qtd) {
    if (!l) return;

    node_t *aux = l->begin;
    int i = 0;

    while (aux != NULL && i < qtd) {
        printf("%s\n", aux->word);
        aux = aux->next;
        i++;
    }
}

void push_node_list(list_t *l, char *word) {
    if (!l) return;
    node_t *n = malloc(sizeof(node_t));

    n->word = word;
    n->next = NULL;

    node_t *aux = l->begin;
    node_t *prev = NULL;

    /*  Searches the position of the node to be inserted in the list.
        for this, an auxiliar node is used and the previus node. */
    while (aux != NULL && strncmp(aux->word, n->word, 1) < 0) {
        prev = aux;
        aux = aux->next;
    }

    //  If the list is empty
    if (l->begin == NULL) {
        n->next = l->begin;

        l->begin = n;
        l->end = n;

        return;
    }
    else {
        //  Insert the node in the middle of the list.
        if (prev != NULL) {
            n->next = prev->next;
            prev->next = n;
        }
        // Inserting the node at the top of the list.
        else {
            n->next = aux;
            l->begin = n;
        }

        if (n->next == NULL)
            l->end = n;
    }

}

void update_array_index(list_t *l, index_t *array) {
    node_t *aux = l->begin;

    for (int i = 0; i < 26 && aux != NULL;) {
    /*  If we are at the first word starting with a letter and that letter is
        the one at the array index, we update the array and skip to the next
        letter. */
        if (!strncmp(aux->word, array[i].firstChar, 1)) {
            array[i].address = aux;
            i++;
        }

    /*  If we are at a word from the list, and we are verifying a char posterior
        in the array, we go through the list until we reach the char that we
        need to verify. */
        if(strncmp(aux->word, array[i].firstChar, 1) < 0)
            aux = aux->next;
    /*  However if we are at a char and the word from the list starts with a
        bigger char, we go through the array index until we reach this char. */
        else 
            i++;
    }
}

int search_list(list_t *l, index_t *a, char *word) {
    node_t *aux = NULL;

    /*  Go through the array until we find which adress starts with the word's
        letter. */
    for (int i = 0; i < 26; i++) {
        if (!strncmp(a[i].firstChar, word, 1))
            aux = a[i].address;
    }

    // If aux is null, then no words start with that same letter.
    if (aux == NULL)
        return -1;

    int i = 0;
    while (aux != NULL && strcmp(aux->word, word) != 0) {
        aux = aux->next;
        i++;
    }

    if (aux == NULL)
        return -1;

    // Verify if the word exists in the list.
    if (strcmp(aux->word, word) != 0) {
        printf("lista: %s, palavra %s\n\n", aux->word, word);
        return -1;
    }

    return i;
}