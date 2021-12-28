#include <stdio.h>
#include <stdlib.h>
#include "list.h"


int main(int argc, char *argv[]) {
    int testCase;
    scanf(" %d", &testCase);

    for(int i = 0; i < testCase; i++) {
        list_t *l = creat_list();

        int sizeList, qtdRotation;
        scanf(" %d %d", &sizeList, &qtdRotation);

        for(int i = 0; i < sizeList; i++) {
            elem x;
            scanf(" %d", &x);
            push(l, x);
        }
        rotate_list(l, qtdRotation);
        print_list(l);
        delete_list(l);
    }

    return 0;
}