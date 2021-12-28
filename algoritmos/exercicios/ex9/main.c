#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


char *read_word();
list_t *soma();
list_t *receive();
int who_big();


int main(int argc, char *argv[]) {
    int qtdOp;
    scanf(" %d", &qtdOp);

    for (int i = 0; i < qtdOp; i++) {
        char *command =  read_word();

        if (!strcmp(command, "SUM")) {
            list_t *s = soma();
            show_list(s);
            free_list(s);
        }
        else if (!strcmp(command, "BIG")) {
            int isBig = who_big();
            if (isBig == 0 || isBig == 1)
                printf("%d\n", isBig);
        }
        else if (!strcmp(command, "SML")) {
            int isBig = who_big();
            if (isBig == 0 || isBig == 1)
                printf("%d\n", !isBig);
            else
                printf("0\n");
        }
        else {
            int isBig = who_big();
            if (isBig == 3)
                printf("1\n");
            else
                printf("0\n");
        }

        free(command);
    }

    return EXIT_SUCCESS;
}

list_t *receive() {
    list_t *l = creat();
    char c = '\0';

    while ((c = getchar()) == '\r' || c == '\n');
    if (c != EOF)
        ungetc(c, stdin);

    while (c != ' ' && c != '\n' && c != '\r') {
        c = getchar();

        if (c != ' ' && c != '\n' && c != '\r')
            push_back(l, c);
    }

    return l;
}

int who_big() {
    list_t *l1 = receive();
    list_t *l2 = receive();

    int isBig = is_big(l1, l2);

    free_list(l1);
    free_list(l2);

    return isBig;
}

list_t *soma() {
    list_t *l1 = receive();
    list_t *l2 = receive();

    int tam = max(l1, l2);
    list_t *s = creat();
    for (int i = 0; i < tam; i++)
        push_back(s, '0');
    
    sum(s,l1);
    sum(s,l2);

    free_list(l1);
    free_list(l2);

    return s;

}

char *read_word() {
    char *w = NULL;
    char c = '\0';
    int count = 0;

    while ((c = getchar()) == '\r' || c == '\n');
    if (c != EOF) {
        ungetc(c, stdin);
    }

    do {
        c = getchar();

        w = realloc(w, ++count * sizeof(char));
        w[count - 1] = c;

    } while(c != ' ' && c != EOF);
    w[count - 1] = '\0';

    return w;
}