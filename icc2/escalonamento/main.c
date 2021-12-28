/**
 * @file main.c
 * @author Vitor da Silveira Paula Nº 10689651
 * @brief Trabalho 03 - Escalonador de processos.
 * SCC0201 - Introdução à Ciência da Computação 2.
 * @version last version.
 * @date 06 de Dezembro.
 * 
 * @copyright Copyright (c) 2021
 * 
 */



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node node_t;
typedef struct list list_t;
typedef struct data data_t;


struct data {
    int code;
    int ti;
    int tf;
    int r;
};

struct node {
    data_t *info;
    node_t *next;
    node_t *prev;
};

struct list {
    node_t *begin;
};


list_t *creat_list();
node_t *push_node_list(list_t *l, data_t *d);
node_t *pop_node_list(list_t *l, data_t *d);
int is_empty(list_t *l);
void destroy_list(list_t *l);
void show_list(list_t *l);
node_t *creat_node(data_t *d);

data_t *create_operation();
data_t **receive_operations();
void heap_sort(data_t **v, int n);
void roud_robin(list_t *l, data_t **v, int size);


int main(int argc, char *argv[]) {
    list_t *l = creat_list();
    int size;

    // Vetor com os dados (cada operação)
    data_t **data = receive_operations(&size);

    // Ordena de acordo com o tempo.
    heap_sort(data, size - 1);

    roud_robin(l, data, size);

    // Desaloco apenas o vetor de ponteiros, pois os ponteiros, a lista desaloca
    // no fim de cada operação.
    free(data);

    destroy_list(l);


    return EXIT_SUCCESS;
}

list_t *creat_list() {
    list_t *l = malloc(sizeof(list_t));

    l->begin = NULL;

    return l;
}

node_t *creat_node(data_t *d) {
    node_t *n = malloc(sizeof(node_t));

    n->info = d;
    n->next = NULL;
    n->prev = NULL;

    return n;
}

/**
 * @brief verifica se a lista está vazia.
 * 
 * @param l 
 * @return int 
 */
int is_empty(list_t *l) {
    if (l->begin == NULL)
        return 1;

    return 0;
}

/**
 * @brief Compara a prioridade entre duas operações, se a prioridade for a mesma
 * compara o código, caso for igual também, retorna 0, pois são iguais.
 * 
 * @param d1 
 * @param d2 
 * @return int 
 */
static int compare(data_t *d1, data_t *d2) {
    if (d1->r < d2->r)
        return 1;
    else if (d1->r > d2->r)
        return -1;
    else if(d1->code < d2->code)
        return -1;
    else if (d1->code > d2->code)
        return 1;

    return 0;
}

node_t *push_node_list(list_t *l, data_t *d) {
    node_t *n = creat_node(d);
    
    // Adicionando em uma lista vazia.
    if (l->begin == NULL) {
        n->next = n;
        n->prev = n;
        l->begin = n;

        return n;
    }
    node_t *aux = l->begin;

    /*  Percorrendo a lista até encontrar o ponto de colocar o novo nó, de acordo
        com os critérios necessários */
    while (aux->next != l->begin && compare(n->info, aux->info) > 0)
        aux = aux->next;

    //  verificando se estou dicionando no fim da lista ou não.
    if (compare(n->info, aux->info) > 0) {
        aux = l->begin;
    }

    n->next = aux;
    n->prev = aux->prev;
    aux->prev->next = n;
    aux->prev = n;


    // Verificando se eu adicionei no começo da lista
    if (aux == l->begin && compare(n->info, aux->info) < 0) {
        l->begin = n;
    }

    return n;
}


node_t *pop_node_list(list_t *l, data_t *d) {
    if (is_empty(l))
        return NULL;

    node_t *aux = l->begin;

    // Verificando se estou retirando em uma lista com um único nó.
    if(aux->next == aux && !compare(aux->info, d)) {
        l->begin = NULL;
        return aux;
    }

    // percorrendo até chegar no nó a ser retirado.
    while (aux->next != l->begin && compare(aux->info, d) != 0) {
        aux = aux->next;
    }

    if (compare(aux->info, d) != 0)
        return NULL;
    
    // Se eu estou retirando do início, início aponta para o próximo.
    if (aux == l->begin)
        l->begin = aux->next;
        
    if (aux->next == aux) {
        l->begin = NULL;
    }
    else {
        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;
    }
    
    return aux;
}

/**
 * @brief Destroi a lista desalocando toda a memória usada dinamicamente.
 * 
 * @param l 
 */
void destroy_list(list_t *l) {
    node_t *aux = l->begin;

    while (aux != NULL) {
        l->begin = aux->next;
        free(aux->info);
        free(aux);
        aux = l->begin;
    }
    free(l);
}

/**
 * @brief Mostra todas as operações que estão na lista.
 * 
 * @param l 
 */
void show_list(list_t *l) {
    node_t *aux = l->begin;

    if (aux == NULL) return;

    while (aux->next != l->begin) {
        printf("%d ", aux->info->code);
        aux = aux->next;
    }
    printf("%d\n", aux->info->code);
    printf("\n");
}

/**
 * @brief recebe uma única operação e a salva em um nó.
 * 
 * @return data_t* 
 */
data_t *create_operation() {
    data_t *d = malloc(sizeof(data_t));
    scanf(" %d %d %d %d", &d->code, &d->ti, &d->tf, &d->r);

    return d;
}

/**
 * @brief Recebe todas as operações, verifica se não tem código repetido, caso
 * sim, trata este problema.
 * 
 * @param x 
 * @return data_t** 
 */
data_t **receive_operations(int *x) {
    data_t **op = NULL;
    int size = 0;

    while (!feof(stdin)) {
        data_t *d = create_operation();
        op = realloc(op, ++size * sizeof(data_t *));

        for (int i = 0; i < size - 1; i++) {
            if(op[i]->code == d->code)
                d->code++;
        }

        op[size - 1] = d;
    }
    *x = size;
    return op;
}

/**
 * @brief Está função dá push numa operação na lista de acordo com que chega no
 * tempo dessa operação entrar. E também, essa função também trabalha no
 * processo.
 * 
 * @param l 
 * @param v 
 * @param size 
 */
void roud_robin(list_t *l, data_t **v, int size) {
    int time = 0;
    int j = 0;
    node_t *currentProcess = NULL;

    while (j < size || !is_empty(l)) {
        time++;
        while (j < size && v[j]->ti == time) {
            // Recebo o ultimo processo adicionado na lista.
            node_t *lastAdd = push_node_list(l, v[j++]);

            /*  Verifico se não está processando nada, ou se o ultimo processo 
                adicionado tem prioridade maior do o que está sendo processado
                tem no momento, para o que o processador processe certo.*/
            if(currentProcess == NULL || (currentProcess->info->r <= lastAdd->info->r))
                currentProcess = lastAdd;
            

        }

        // Se não está processando nada, volta ao início da função.
        if (currentProcess == NULL)
            continue;

        /*  Retira um do volume de quantum necessário para ser completamente 
            executado(tf), pois quando esse tf chegar a zero, é o momento de
            retirar da lista */
        currentProcess->info->tf -= 1;

        if (currentProcess->info->tf > 0) {
            currentProcess = currentProcess->next;
            continue;
        }

        /*  Nesta caso, o tf processo da operação é igual a zero
            ou seja, a operação está pronta para sair da lista*/
        node_t *node = pop_node_list(l, currentProcess->info);

        // Verificação se tinha apena um elemento na lista
        if (currentProcess == currentProcess->next)
            currentProcess = NULL;
        else 
            currentProcess = currentProcess->next;

        if (node != NULL) {
            printf("%d %d\n", node->info->code, time);
            free(node->info);
            free(node);
        }
    }
}

void max_heapify(data_t **v, int node, int n) {
    int f = (node * 2) + 1;

    if (f > n) return;
    
    if (v[f]->ti > v[node]->ti || (f + 1 <= n && v[f + 1]->ti > v[node]->ti) ) {
        if (f + 1 <= n && v[f + 1]->ti > v[f]->ti)
            f = f + 1;

        data_t *tmp = v[node];
        v[node] = v[f];
        v[f] = tmp;

        max_heapify(v, f, n);
    }
}

/**
 * @brief Ordena o vetor de processos de acordo o tempo de entrada do processo.
 * 
 * @param v 
 * @param n 
 */
void heap_sort(data_t **v, int n) {
    if (n < 1) return;

    int m = (int)n / 2;

    for (int i = m; i >= 0; i--)
        max_heapify(v, i, n);

    while (n >= 1) {
        data_t *tmp = v[0];
        v[0] = v[n];
        v[n] = tmp;

        n--;
        max_heapify(v, 0, n);
    }
}