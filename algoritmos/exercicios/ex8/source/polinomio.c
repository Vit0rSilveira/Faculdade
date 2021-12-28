#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "polinomio.h"


#define IGNORA(c) (c == '(' || c ==',' || c == ' ')
#define FIM(a) (a == ')' || a == '\r' || a == '\n')

struct poli {
    list_t **p;
    int qtd;
};

static void my_assert(int x) {
    if (!x)
        exit(EXIT_FAILURE);
}

polynomial_t *creat_polynomial() {
    polynomial_t *p = malloc(sizeof(polynomial_t));
    my_assert(p != NULL);
    
    p->p = NULL;
    p->qtd = 0;

    return p;
}

void add_polynomial(polynomial_t *p) {
    my_assert(p != NULL);

    p->p = realloc(p->p, ++p->qtd * sizeof(list_t *));
    p->p[p->qtd - 1] = creat_list();

    char c = 0;
    while ((c = getchar()) == '\n' || c == '\r');
    if (c != EOF)
        ungetc(c, stdin);

    while(1) {
        c = getchar();

        if(FIM(c))
            break;

        if(!IGNORA(c)) {
            ungetc(c, stdin);

            int x;
            scanf("%d", &x);
            push_list(p->p[p->qtd - 1], x);
        }

    }
}

static void print_elem(elem x, int begin, int end) {
    if (begin)
        printf("(");

    printf("%d", x);

    if (end)
        printf(")\n");
    else
        printf(",");
}

void show_p(list_t *l) {
    my_assert(l != NULL);

    show_list(l, print_elem);
}

void show_polynomial(polynomial_t *p) {
    my_assert(p != NULL);

    for (int i = 0; i < p->qtd; i++) {
        show_p(p->p[i]);
    }
}

static int tam_sum(polynomial_t *p) {
    int maior = 0;
    for (int i = 0; i < p->qtd; i++) {
        if (maior < size_list(p->p[i]))
            maior = size_list(p->p[i]);
    }

    return maior;
}

void sum_elem(int *x_sum, int *y_poli) {
    *x_sum += *y_poli;
}

list_t *sum_polynomial(polynomial_t *p) {
    my_assert(p != NULL);

    list_t *sum = creat_list();
    for (int i = 0; i < tam_sum(p); i++) {
        push_list(sum, 0);
    }

    for (int i = 0; i < p->qtd; i++) {
        access_elements(sum, p->p[i], sum_elem);
    }
    
    return sum;
}

void free_polynomial(polynomial_t *p) {
    my_assert(p != NULL);

    if (p->qtd != 0) {
        for (int i = 0; i < p->qtd; i++)
            free_list(p->p[i]);
    }

    free(p->p);
    free(p);
}