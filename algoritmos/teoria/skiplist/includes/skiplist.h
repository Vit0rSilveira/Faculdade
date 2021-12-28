#ifndef SKIPLIST_H
#define SKIPLIST_H

#define NIVEL_MAX 20

typedef struct skiplist skiplist_t;

skiplist_t *creat();
int push(skiplist_t *sk, int x);
int remove_elem(skiplist_t *sk, int x);
void show(skiplist_t *sk);
int kill(skiplist_t *sk);
int search(skiplist_t *sk, int x);
int alter(skiplist_t *sk, int x);

#endif