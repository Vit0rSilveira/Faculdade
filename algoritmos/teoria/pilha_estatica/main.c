#include<stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main(int argc, char* argv[]) {
    stack_t *p;

    p = create();

    int num;
    scanf("%d", &num);

    while(num > 0) {
        push(p, num % 2);

        num = num / 2;
    }

    int x;
    while (!isEmpty(p)) {
        pop(p, &x);
        printf("%d ", x);
    }
    printf("\n");

    destroy(p);

    return 0;
}