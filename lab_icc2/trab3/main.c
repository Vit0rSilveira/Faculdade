#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "huffman.h"


char *read_line();

int main(int argc, char *argv[]) {
    char *c = read_line();

    tree_t *t = create_huffman(c);
    table_t *cp = create_array_compress(t);

    char *stringComprees = compress_phrase(cp, c);

    char *phrase = decompress_phrase(stringComprees, t);
    
    printf("%s\n", phrase);
    printf("Indice de compressao: %.2lf\n", calc_tax_compress(phrase, stringComprees));

    free(c);
    free(phrase);
    free(stringComprees);
    delete_array_compress(cp);
    delete_huffman(t);

    return EXIT_SUCCESS;
}

bool is_end_line(char c) {
    if (c == '\n' || c == '\r')
        return true;

    return false;
}

/**
 * @brief Lê uma linha.
 * 
 * @return char* 
 */
char *read_line() {
    char *line = NULL;
    int i = 0;
    char c = '\0';

    while (is_end_line(c = getchar()));
    if (c != EOF) ungetc(c, stdin);

    do {
        c = getchar();

        line = realloc(line, ++i * sizeof(char));
        line[i - 1] = c;


    } while(!is_end_line(c) && c != EOF);
    line[i - 1] = '\0';

    return line;
}