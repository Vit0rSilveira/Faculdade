#include <stdlib.h>
#include <stdio.h>

typedef struct no lista_t;

struct no {
    int info;
    lista_t *prox;
};


int main(int argc, char *argv[]) {
    lista_t *ini, *fim, *p;
    ini = NULL;
    fim = NULL;

    int num;
    scanf(" %d", &num);

    while(num != -1) {
        p = (lista_t *)malloc(sizeof(lista_t));
        p->info = num;
        p->prox = NULL;

        if(ini == NULL) { //Lista esta vazia
            ini = p;
            fim = p;
        }
        else {
            fim->prox = p;
            fim = p;
        }
        scanf(" %d", &num);
    }

    p = ini;
    while(p != NULL) {
        printf("%d ", p->info);
        p = p->prox;
    }

    while(ini != NULL) {
        p = ini;
        ini = ini->prox;
        free(p);
    }

    return 0;
}