#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "data.h"


int main(int argc, char *argv[]) {
    while(!is_end()) {
        stack_t *s = creat_stack();

        elem c = '\0';

        do {
            c = getchar();
            if(is_input(c)) {
                push(s, c);
            }
            else if(is_output(c)) {
                if(is_opposite(pick(s), c))
                    pop(s);
                else
                    push(s,c);
            }
            else if (is_specialCase(c)) {
                if(pick(s) == c)
                    pop(s);
                else
                    push(s, c);
            }
        } while(!is_endLine(c) && c != EOF);
        
        if(is_empty(s))
            printf("BALANCEADO\n");
        else
            printf("NÃO BALANCEADO\n");
        
        delete_stack(s);
    }

    return 0;
}