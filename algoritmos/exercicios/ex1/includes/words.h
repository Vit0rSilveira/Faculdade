#ifndef WORDS_H
#define WORDS_H

typedef struct phrase phrase_t;

/**
 * @brief Receive the words in the phrase and count the repetitions, and don't
 * receive repeted words, only add one more its repetitions
 * 
 * @return phrase_t* 
 */
phrase_t *receive_phrase();

/**
 * @brief Order the words according to number of repetitions. If number is the
 * same, sort alphabetically 
 * 
 * @param phrase 
 */
void insertion_sort(phrase_t *phrase);

void print_requested(phrase_t *phrase);

/**
 * @brief Consumes the '\r' and '\n' and return if it's EOF or no
 * 
 * @return int 
 */
int is_end();

void free_memory(phrase_t *phrase);

#endif