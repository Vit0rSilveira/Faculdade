#ifndef SUB_H
#define SUB_H

typedef struct information info_t;


/**
 * @brief Recieve the phrase, the wrong word or phrase, and correct word
 * and saved in the struct info_t
 * 
 * @return info_t* 
 */
info_t *recieve_informations();

/**
 * @brief This function create a new phrase, with the replacement.
 * For the replace, the function walk the phrase with error, case not finded
 * copy the char for the new phrase. If find the error, put the right word in
 * the new phrase.
 * 
 * @param informations 
 * @return char* correct phrase
 */
char *replace_word(info_t *informations);

/**
 * @brief Consumes the '\r' and '\n' and return if it's EOF or no
 * 
 * @return int 
 */
int is_end();

void free_memory(info_t *informations, char *phrase);

#endif