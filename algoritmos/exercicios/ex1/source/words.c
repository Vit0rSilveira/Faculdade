#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "words.h"

typedef struct word {
    char *word;
    int qtdRepeat;
} word_t;

struct phrase {
    word_t *words;
    int qtd;
};


/**
 * @brief Compare de words, firts by numbers of repetitions. If necessary,
 * compare with the alphabetical order.
 * 
 * @param w1 
 * @param w2 
 * @return int
 */
static int make_change(word_t *w1, word_t *w2) {
    if(w2->qtdRepeat > w1->qtdRepeat)
        return 1;
    else if (w1->qtdRepeat == w2->qtdRepeat) {
        if (strcmp(w2->word, w1->word) < 0)
            return 1;
    }
    return 0;
}

/**
 * @brief Verify if the word already exist in phrase
 * 
 * @param phrase phrase for the analytcs
 * @param word word fot the comparation
 * @return int word's index in the phrase, if the word exist
 */
static int word_exist(phrase_t *phrase, char *word) {
    for(int i = 0; i < phrase->qtd; i++) {
        if (!strcmp(phrase->words[i].word, word))
            return i;
    }

    return -1;
}

static int is_endLine(char c) {
    if(c == '\n' || c == '\r')
        return 1;
    
    return 0;
}

static char *read_word(int *endphrase) {
    char *line = NULL;
    char c = '\0';
    int count = 0;

    is_end();

    do {
        c = getchar();
        
        line = realloc(line, ++count * sizeof(char));
        line[count - 1] = c;

        if (is_endLine(c) || c == EOF)
            *endphrase = 0;

    } while(!is_endLine(c) && c != ' ' && c != EOF);
    line[count - 1] = '\0';

    return line;
}

int is_end() {
    char c = '\0';
    while(is_endLine(c = getchar()));

    if(c != EOF) {
        ungetc(c, stdin);
        return 1;
    }
    
    return 0;
}

phrase_t *receive_phrase() {
    phrase_t *phrase = malloc(sizeof(phrase_t));
    phrase->words = NULL;
    phrase->qtd = 0;

    int endphrase = 1;

    
    while(endphrase) {
        char *word = read_word(&endphrase);
        int index = word_exist(phrase, word);

        if(index == -1) {
            phrase->words = realloc(phrase->words, ++(phrase->qtd) * sizeof(word_t));
            phrase->words[phrase->qtd - 1].word = word;
            phrase->words[phrase->qtd - 1].qtdRepeat = 1;
        }
        else {
            (phrase->words[index].qtdRepeat)++;
            free(word);
        }

    }

    return phrase;

}

void insertion_sort(phrase_t *phrase) {

    for (int j = 1; j < phrase->qtd; j++) {
        word_t chave = phrase->words[j];
        int i = j - 1;
        
        while((i >= 0) && make_change(&phrase->words[i], &chave)) {
            phrase->words[i + 1] = phrase->words[i];
            i = i - 1;
        } 
        phrase->words[i + 1] = chave;
    }
}

void print_requested(phrase_t *phrase) {
    int qtd;
    scanf(" %d", &qtd);
    for(int i = 0; i < qtd && i < phrase->qtd; i++)
        printf("%s %d\n", phrase->words[i].word, phrase->words[i].qtdRepeat);
}

void free_memory(phrase_t *phrase) {
    for(int i = 0; i < phrase->qtd; i++)
        free(phrase->words[i].word);

    free(phrase->words);
    free(phrase);
}