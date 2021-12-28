#include <stdio.h>
#include "words.h"


int main() {

    while(is_end()) {
        phrase_t *my_phrase = receive_phrase();
        insertion_sort(my_phrase);
        
        print_requested(my_phrase);
        free_memory(my_phrase);
        
        if(is_end())
            printf("\n");
    }

    return 0;
}