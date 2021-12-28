#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>


enum casos {PIOR, NORMAL, MELHOR};

#define MAX_RAND 2000

struct tempos{
    double tBubble;
    double tInsertion;
    double tMerge;
};

typedef struct tempos tempos_t;

int *gerar_vetor(int casos, int tamanho);

void insertion_sort(int *vetor, int tamanho);
void merge_sort(int *vetor, int ini, int fim);
void bubble_sort(int *vetor, int tamanho);

void criar_cabecalho(char *nome, bool normal);

tempos_t comparar(int *vetor, int tam);

void salvar_normal(int tam, tempos_t *media);
void salvar_mp(char *caso, tempos_t *media);


//https://www.ic.unicamp.br/~afalcao/mc102/slides_aula13.pdf


int main(int argc, char *argv[]) {
    int tamanhos[] = {25, 100, 1000, 3000, 7000, 10000, 15000, 20000};
    criar_cabecalho("Dados.csv", true);

    int *vetorBaseNormal = gerar_vetor(NORMAL, 20000);
    for(int i = 0; i < 8; i++) {

        for(int j = 0; j < 10; j++) {
            tempos_t tempos = comparar(vetorBaseNormal, tamanhos[i]);
            salvar_normal(tamanhos[i], &tempos);
        }
    }
    free(vetorBaseNormal);

    criar_cabecalho("DadosMP.csv", false);

    int *vetorBasePior = gerar_vetor(PIOR, 1000);
    for(int i = 0; i < 10; i++) {
        tempos_t tempos = comparar(vetorBasePior, 1000);
        salvar_mp("Pior",&tempos);
    }
    free(vetorBasePior);

    int *vetorBaseMelhor = gerar_vetor(MELHOR, 1000);
    for(int i = 0; i < 10; i++) {
        tempos_t tempos = comparar(vetorBaseMelhor, 1000);
        salvar_mp("Melhor",&tempos);
    }
    free(vetorBaseMelhor);

    return EXIT_SUCCESS;
}

int *gerar_vetor(int casos, int tam) {
    int *vetor;
    if(casos == PIOR) {
        vetor = (int *)malloc(tam * sizeof(int));

        for(int i = tam, j = 0; i > 0; i--, j++)
            vetor[j] = i;
    }
    else if (casos == NORMAL) {
        vetor = (int *)malloc(tam * sizeof(int));

        for(int i = 0; i < tam; i++)
            vetor[i] = rand() % MAX_RAND;
    }
    else {
        vetor = (int *)malloc(tam * sizeof(int));

        for(int i = 0; i < tam; i++)
            vetor[i] = i;
    }

    return vetor;
}

void criar_cabecalho(char *nome, bool normal) {
    FILE *arquivo = NULL;
    arquivo = fopen(nome, "w");
    if(normal)
        fprintf(arquivo, "Tamanho,Bubble Sort,Insertion Sort,Merge Sort\n");
    else
        fprintf(arquivo, "Caso,Bubble Sort,Insertion Sort,Merge Sort\n");
    fclose(arquivo);
}

void bubble_sort(int *vetor, int tamanho) {
    for(int i = tamanho - 1; i > 0; i--) {
        for(int j = 0; j < i; j++) {
            if(vetor[j] > vetor[j + 1]) {
                int aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void insertion_sort(int *vetor, int tamanho) {
    for(int i = 1; i < tamanho; i++) {
        int chave = vetor[i];
        int j = i - 1;

        while((j >= 0) && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
}

void  merge(int *vetor, int ini, int m, int fim) { 
    int size = fim - ini + 1; 
    int *copia = malloc(size * sizeof(int));

    int p1 = ini;
    int p2 = m + 1;

    for(int i = 0; i < size; i++) {
        if (p1 <= m && p2 <= fim) {
            if(vetor[p1] > vetor[p2])
                copia[i] = vetor[p2++];
            else
                copia[i] = vetor[p1++];
        }
        else {
            if (p1 > m)
                copia[i] = vetor[p2++];
            else
                copia[i] = vetor[p1++];
        }
    }

    int j = ini;
    for(int i = 0; i < size; i++)
        vetor[j++] = copia[i];
    
    free(copia);
}

void merge_sort(int *vetor, int ini, int fim) {
    if (fim <= ini) return;

    int m = (fim + ini) / 2;

    merge_sort(vetor, ini, m);
    merge_sort(vetor, m + 1, fim);

    merge(vetor, ini, m, fim);

}

double calcular_media(double *vetor) {
    double media = 0.0;
    for(int i = 0; i < 10; i++) {
        media += vetor[i];
    }
    
    return media / 10;
}

void salvar_normal(int tam, tempos_t *media) {
    FILE *arquivo = NULL;
    arquivo = fopen("Dados.csv", "a");
    fprintf(arquivo, "%d,%lf,%lf,%lf\n",
            tam, media->tBubble, media->tInsertion, media->tMerge);
    fclose(arquivo);
}

void salvar_mp(char *caso, tempos_t *media) {
    FILE *arquivo = NULL;
    arquivo = fopen("DadosMP.csv", "a");
    fprintf(arquivo, "%s,%lf,%lf,%lf\n", 
            caso, media->tBubble, media->tInsertion, media->tMerge);
    fclose(arquivo);
}

tempos_t comparar(int *vetor, int tam) {
    int *vetorCopiaB = calloc(tam,  sizeof(int));
    int *vetorCopiaI = calloc(tam,  sizeof(int));
    int *vetorCopiaM = calloc(tam,  sizeof(int));

    for(int i = 0; i < tam; i++) {
        vetorCopiaB[i] = vetor[i];
        vetorCopiaI[i] = vetor[i];
        vetorCopiaM[i] = vetor[i];
    }

    tempos_t tempo;
    clock_t c1, c2;

    c1 = clock();
    bubble_sort(vetorCopiaB, tam);
    c2 = clock();
    tempo.tBubble = (c2 - c1) / (double) CLOCKS_PER_SEC;

    c1 = clock();
    insertion_sort(vetorCopiaI, tam);
    c2 = clock();
    tempo.tInsertion = (c2 - c1) / (double) CLOCKS_PER_SEC;

    c1 = clock();
    merge_sort(vetorCopiaM, 0, tam - 1);
    c2 = clock();
    tempo.tMerge = (c2 - c1) / (double) CLOCKS_PER_SEC;


    free(vetorCopiaB);
    free(vetorCopiaI);
    free(vetorCopiaM);

    printf("Bubble: %lf Insertion: %lf Merge: %lf\n", tempo.tBubble, tempo.tInsertion, tempo.tMerge);


    return tempo;
}