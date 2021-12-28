#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "banco.h"

char *read_name();
int is_end();
char *read_command();
void insert_person(banco_t *b);
void remove_person(banco_t *b);


int main() {
    banco_t *b = creat();


    while (!is_end()) {
        char *Command = read_command();

        if(!strcmp(Command, "INSERE"))
            insert_person(b);
        else if (!strcmp(Command, "REMOVE"))
            remove_person(b);
        else
            imprimir(b);
        
        free(Command);
    }

    free_bank(b);

    return EXIT_SUCCESS;
}

void insert_person(banco_t *b) {
    int code;
    scanf(" %d", &code);
    char *name = read_name();

    if(strlen(name) > 50) {
        free(name);
        printf("INVALIDO\n");
        return;
    }

    insert(b, code, name);
}

void remove_person(banco_t *b) {
    int code;
    scanf(" %d", &code);

    remove_elem(b, code);
}

int is_end_line(char c) {
    if(c == '\r' || c == '\n')
        return 1;
    
    return 0;
}

char *read_name() {
    char *name = NULL;
    char caractere = '\0';
    int count = 0;

    while (is_end_line(caractere = getchar()) || caractere == ' ');
    if (caractere != EOF)
        ungetc(caractere, stdin);
    
    do {
        caractere = getchar();

        name = realloc(name, ++count * sizeof(char));
        name[count - 1] = caractere;

    } while (!is_end_line(caractere) && caractere != EOF);
    name[count - 1] = '\0';

    return name;
}

char *read_command() {
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

int is_end() {
    char c = '\0';
    while(is_end_line(c = getchar()));

    if(c != EOF) {
        ungetc(c, stdin);
        return 0;
    }
    
    return 1;
}