#ifndef POLINOMIO_H
#define POLINOMIO_H

typedef struct poli polynomial_t;

polynomial_t *creat_polynomial();
void add_polynomial(polynomial_t *p);
void show_polynomial(polynomial_t *p);
list_t *sum_polynomial(polynomial_t *p);
void free_polynomial(polynomial_t *p);
void show_p(list_t *l);

#endif