#include "ex2.h"

int main(int argc, char *argv[]) {
    int *vetor_primos = gerar_primos();
    mostrar_primos(vetor_primos);
    liberar_memoria(vetor_primos);

    return 0;   
}