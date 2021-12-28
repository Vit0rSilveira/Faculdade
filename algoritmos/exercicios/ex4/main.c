#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"


typedef struct person {
    char *name;
    int age;
    int sick;
} person_t;

void put_person(queue_t **queue);
void out_person(queue_t **queue);
char *read_line();
void destroy(queue_t **q);
void free_person(person_t *p);


int main() {
    int qtd;
    scanf(" %d", &qtd);

    queue_t **q = calloc(4,  sizeof(queue_t *));
    for(int i = 0; i < 4; i++)
        q[i] = create_queue(sizeof(person_t));
    
    for (int i = 0; i < qtd; i++) {
        char *command = read_line();

        if(!strcmp(command, "ENTRA"))
            put_person(q);
        else if(!strcmp(command, "SAI"))
            out_person(q);
        
        free(command);
    }

    destroy(q);

    return 0;
}

void free_person(person_t *p) {
    free(p->name);
    free(p);
}

void destroy(queue_t **q) {
    for(int i = 0; i < 4; i++) {
        delete_queue(q[i], (free_fun)free_person);
    }
    free(q);
}

person_t receive_person() {
    person_t p;

    p.name = read_line();
    scanf(" %d", &p.age);
    scanf(" %d", &p.sick);

    return p;
}

int seleciton_queue(person_t *p) {
    if (p->age >= 60 && p->sick == 1)
        return 0;
    else if (p->sick)
        return 1;
    else if(p->age >= 60)
        return 2;
    else
        return 3;
}

void put_person(queue_t **queue) {
    person_t p = receive_person();
    
    int priority = seleciton_queue(&p);

    push(queue[priority], &p);
}

void print_person(person_t *p) {
    printf("%s %d %d\n", p->name, p->age, p->sick);
}

void out_person(queue_t **queue) {
    person_t *p;

    if(!is_empty(queue[0]))
        p = pop(queue[0]);
    else if(!is_empty(queue[1]))
        p = pop(queue[1]);
    else if(!is_empty(queue[2]))
        p = pop(queue[2]);
    else if(!is_empty(queue[3]))
        p = pop(queue[3]);
    else {
        printf("FILA VAZIA\n");
        return;
    }

    print_person(p);
    free_person(p);
}

int is_space(char c) {
    if(c == ' ' || c == '\r' || c == '\n')
        return 1;
    
    return 0;
}

char *read_line() {
    char *name = NULL;
    char caractere = '\0';
    int cout = 0;

    while (is_space(caractere = getchar()));
    if (caractere != EOF)
        ungetc(caractere, stdin);
    
    do {
        caractere = getchar();

        name = realloc(name, ++cout * sizeof(char));
        name[cout - 1] = caractere;

    } while (!is_space(caractere) && caractere != EOF);
    name[cout - 1] = '\0';

    return name;
}