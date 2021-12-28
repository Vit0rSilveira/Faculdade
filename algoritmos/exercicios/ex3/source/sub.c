#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sub.h"


struct information {
    char *phrase;
    char *error;
    char *wordRight;
};


static int is_endLine(char c) {
    if(c == '\n' || c == '\r')
        return 1;

    return 0;
}

static char *read_phrase_or_Word() {
    char *line = NULL;
    char c = '\0';
    int count = 0;

    is_end();

    do {
        c = getchar();
        
        line = realloc(line, ++count * sizeof(char));
        line[count - 1] = c;

    } while(!is_endLine(c) && c != EOF);
    line[count - 1] = '\0';

    return line;
}

info_t *recieve_informations() {
    info_t *dado = malloc(sizeof(info_t));
    
    dado->phrase = read_phrase_or_Word();
    dado->error = read_phrase_or_Word();
    dado->wordRight = read_phrase_or_Word();

    return dado;
}

int is_end() {
    char c = '\0';
    while(is_endLine(c = getchar()));

    if(c != EOF) {
        ungetc(c, stdin);
        return 0;
    }
    
    return 1;
}

char  *replace_word(info_t *informations) {
    int tamPhrase = strlen(informations->phrase);
    int tamError = strlen(informations->error);
    int tamRight = strlen(informations->wordRight);

    char *newPrash = NULL;

    int j = 0;
    for (int i = 0; i < tamPhrase;) {
        if(strncmp(informations->phrase + i, informations->error, tamError) == 0) {
            j += tamRight;
            int k = j - tamRight;
            
            newPrash = realloc(newPrash, j * sizeof(char));
            memcpy(newPrash + k, informations->wordRight, tamRight);

            i += tamError;
        }
        else {
            newPrash = realloc(newPrash, ++j * sizeof(char));
            newPrash[j - 1] = informations->phrase[i++];
        }
    }
    newPrash = realloc(newPrash, ++j * sizeof(char));
    newPrash[j - 1] = '\0';

    return newPrash;
}

void free_memory(info_t *informations, char *phrase) {
    free(phrase);
    free(informations->phrase);
    free(informations->error);
    free(informations->wordRight);
    free(informations);
}