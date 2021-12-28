#ifndef PRIMOS_H
#define PRIMOS_H

#define MAX 10001
#define false 0
#define true 1


/**
 * @brief Gera todos os numeros primos entre o intervalo de zero ao máximo.
 * 
 * @return int* retorna um vetor com os números primos em ordem.
 */
int *gerar_primos();

/**
 * @brief Recebe o a quantidade do número a serem mostrados e o índice de cada
 * número.
 * 
 * @param vetor_primos Vetor com os números primos.
 */
void mostrar_primos(int *vetor_primos);
void liberar_memoria(int *vetor_primos);

#endif