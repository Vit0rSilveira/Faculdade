#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "skiplist.h"

int main (int argc, char *argv[]) {
    skiplist_t *sk = creat();

    for (int i = 0; i < 10000; i++)
        push(sk, rand() % 100000);

    show(sk);
    remove_elem(sk, 38);
    printf("\n");
    show(sk);
    kill(sk);

    return EXIT_SUCCESS;
}