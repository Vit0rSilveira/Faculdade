#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sub.h"


int main(int argc, char *argv[]) {

    while(!is_end()) {
        info_t *myData = recieve_informations();
        char *newphrase = replace_word(myData);
        printf("%s\n", newphrase);

        free_memory(myData, newphrase);
    }

    return 0;
}