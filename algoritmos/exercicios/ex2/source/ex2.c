#include <stdio.h>
#include <stdlib.h>
#include "ex2.h"

struct numero {
    int numero;
    int primo;
};

typedef struct numero numero_t;

static numero_t *receber_numeros() {
    numero_t *vetor = malloc(MAX * sizeof(numero_t));

    for(int i = 0; i < MAX; i++) {
        vetor[i].numero = i;
        vetor[i].primo = true;
    }

    return vetor;
}

static void verificar_primo(numero_t *vetor) {
    for(int i = 2; i < MAX; i++) {
        for(int j = i + 1; j < MAX; j++) {
            if(vetor[j].numero % vetor[i].numero == 0)
                vetor[j].primo = false;
        }
    }
}

int *gerar_primos() {
    numero_t *numeros = receber_numeros();
    verificar_primo(numeros);

    int *primos = NULL;
    int j = 0;
    for (int i = 2; i < MAX; i++) {
        if (numeros[i].primo == true) {
            primos = realloc(primos, ++j * sizeof(int));
            primos[j - 1] = numeros[i].numero;
        }
    }

    free(numeros);
    return primos;
}

void liberar_memoria(int *vetor_primos) {
    free(vetor_primos);
}

void mostrar_primos(int *vetor_primos) {
    int qtd;
    scanf(" %d", &qtd);
    for(int i = 0; i < qtd; i++) {
        int indice;
        scanf(" %d", &indice);
        printf("%d ", vetor_primos[indice - 1]);
    }
    printf("\n");
}