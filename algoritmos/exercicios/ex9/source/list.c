#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct node no_t;

struct node {
    elem info;
    no_t *prox;
    no_t *ant;
};

struct list {
    no_t *ini;
    no_t *fim;
    boolean neg;
    int qtd;
};

list_t *creat() {
    list_t *l = malloc(sizeof(list_t));

    l->ini = NULL;
    l->fim = NULL;
    l->qtd = 0;
    l->neg = FALSE;

    return l;
}

void free_list(list_t *l) {
    no_t *aux = l->ini;

    while (aux != NULL) {
        l->ini = aux->prox;
        free(aux);
        aux = l->ini;
    }
    free(l);
}

void push_back(list_t *l, elem x) {
    if (x == '-') {
        l->neg = TRUE;
        return;
    }

    no_t *n = malloc(sizeof(no_t));

    n->info = x;
    n->prox = NULL;
    n->ant = NULL;

    if (l->ini == NULL) {
        n->prox = l->ini;
        n->ant = l->ini;
        l->ini = n;
        l->fim = n;
    }
    else {
        n->ant = l->fim;
        n->prox = l->fim->prox;
        l->fim->prox = n;
        l->fim = n;
    }
    l->qtd++;
}

void push_front(list_t *l, elem x) {
    no_t *n = malloc(sizeof(no_t));

    n->info = x;
    n->prox = NULL;
    n->ant = NULL;

    n->ant = l->ini->ant;
    n->prox = l->ini;
    l->ini->ant = n;
    l->ini = n;

    l->qtd++;
}

void show_list(list_t *l) {

    while (l->ini->info == '0') {
        no_t *aux1 = l->ini;
        l->ini = l->ini->prox;
        free(aux1);
    }
    no_t *n = l->ini;
    
    if (l->neg == TRUE)
        printf("-");

    while(n != NULL) {
        printf("%d", n->info - '0');
        n = n->prox;
    }

    printf("\n");
}

int max(list_t *l1, list_t *l2) {
    if (l1->qtd > l2->qtd)
        return l1->qtd;
    else if (l2->qtd > l1->qtd)
        return l2->qtd;

    return l1->qtd;
}

int min(list_t *l1, list_t *l2) {
    if (l1->qtd < l2->qtd)
        return l1->qtd;
    else if (l2->qtd < l1->qtd)
        return l2->qtd;

    return l1->qtd;
}

void sum(list_t *s, list_t *l) {
    //int menor = min(s, l);
    int maior = max(s, l);

    no_t *aux1 = s->fim;
    no_t *aux2 = l->fim;
    int soma = 0;
    int sobe = 0;
    for (int i = 0; i < maior; i++) {
        if (aux2 == NULL) {
            int a1 = aux1->info - '0';

            soma = (a1 + sobe) % 10;
            aux1->info = soma + '0';

            sobe = (a1 + sobe) / 10;
            if (i == maior - 1 && sobe != 0) {
                push_front(s, sobe + '0');
            }
            
            aux1 = aux1->ant;            
        }
        else {
            int a1 = aux1->info - '0';
            int a2 = aux2->info - '0';

            soma = (a1 + a2 + sobe) % 10;
            aux1->info = soma + '0';

            sobe = (a1 + a2 + sobe) / 10;
            if (i == maior - 1 && sobe != 0) {
                push_front(s, sobe + '0');
            }
            
            aux1 = aux1->ant;
            aux2 = aux2->ant;
        }
    }
}

int is_big(list_t *l1, list_t *l2) {
    if (!l1->neg && l2->neg)
        return 1;
    else if (l1->neg && !l2->neg)
        return 0;
    else {
        if (l1->qtd > l2->qtd)
            return 1;
        else if (l2->qtd > l1->qtd)
            return 0;
        else {
            no_t *aux1 = l1->ini;
            no_t *aux2 = l2->ini;

            while (aux1 != NULL) {
                if (aux1->info > aux2->info)
                    return 1;
                else if (aux2->info > aux1->info)
                    return 0;
                aux1 = aux1->prox;
                aux2 = aux2->prox;
            }
        }
    }
    return 3;
}