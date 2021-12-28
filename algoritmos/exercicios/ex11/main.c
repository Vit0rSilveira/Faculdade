#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

char *read_string();
void show_tree(tree_t *t);

int main(int argc, char *agrv[]) {
    tree_t *t = creat();

    while (!feof(stdin)) {
        char *c = read_string();

        if (!strcmp(c, "insercao")) {
            int x;
            scanf(" %d", &x);

            push_node(&t->root, x);
        }
        else if (!strcmp(c, "impressao")) {
            show_tree(t);
        }
        free(c);
    }

    finish_node_tree(t->root);
    free(t);

    return EXIT_SUCCESS;
}

void show_tree(tree_t *t) {
    char *type = read_string();

    if (!strcmp(type, "pre-ordem")) {
        if(!pre_order(t->root))
            printf("VAZIA\n");
        else 
            printf("\n");
    }
    else if (!strcmp(type, "em-ordem")) {
        if(!in_order(t->root))
            printf("VAZIA\n");
        else
            printf("\n");
    }
    else if (!strcmp(type, "pos-ordem")) {
        if(!pos_order(t->root))
            printf("VAZIA\n");
        else 
            printf("\n");
    }

    free(type);
}

int is_end_line(char c) {
    if(c == '\r' || c == '\n')
        return 1;
    
    return 0;
}

char *read_string() {
    char *command = NULL;
    char c = '\0';
    int count = 0;

    while (is_end_line(c = getchar()) && c == ' ');
    if (c != EOF)
        ungetc(c, stdin);

    do {
        c = getchar();

        command = realloc(command, ++count * sizeof(char));
        command[count - 1] = c;

    } while(!is_end_line(c) && c != EOF && c != ' ');
    command[count - 1] = '\0';

    return command;
}