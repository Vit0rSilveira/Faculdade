#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

enum casos {PIOR, NORMAL, MELHOR};

#define MAX_RAND 10000

struct tempos{
    double tQuick;
    double tHeap;
};

typedef struct tempos tempos_t;

int *gerar_vetor(int casos, int tamanho);

void criar_cabecalho(char *nome, bool normal);

void heap_sort(int *v, int n);
void quickSort(int *V, int ini, int fim);
int pivo_center(int begin, int end);
int pivo_ini(int begin, int end);

void mostrar_vetor(int *v, int tam) {
    for (int i = 0; i < tam; i++)
        printf("%d ", v[i]);
    printf("\n\n");
}

tempos_t comparar(int *vetor, int tam);

void salvar_normal(int tam, tempos_t *media);
void salvar_mp(char *caso, tempos_t *media);


//https://www.ic.unicamp.br/~afalcao/mc102/slides_aula13.pdf


int main(int argc, char *argv[]) {
    int tamanhos[] = {10, 100, 1000, 10000, 35000, 70000, 100000};
    criar_cabecalho("Dados2.csv", true);

    int *vetorBaseNormal = gerar_vetor(NORMAL, 100000);
    for(int i = 0; i < 7; i++) {

        for(int j = 0; j < 10; j++) {
            tempos_t tempos = comparar(vetorBaseNormal, tamanhos[i]);
            salvar_normal(tamanhos[i], &tempos);
        }
    }
    free(vetorBaseNormal);

    /* criar_cabecalho("DadosMP2.csv", false);

    int *vetorBasePior = gerar_vetor(PIOR, 1000);
    for(int i = 0; i < 10; i++) {
        tempos_t tempos = comparar(vetorBasePior, 1000);
        salvar_mp("Pior",&tempos);
    }
    free(vetorBasePior);

    int *vetorBaseMelhor = gerar_vetor(NORMAL, 1000);
    for(int i = 0; i < 10; i++) {
        tempos_t tempos = comparar(vetorBaseMelhor, 1000);
        salvar_mp("Melhor",&tempos);
    }
    free(vetorBaseMelhor); */

    return EXIT_SUCCESS;
}

void swap (int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int *gerar_vetor(int casos, int tam) {
    int *vetor;
    if(casos == PIOR) {
        vetor = (int *)malloc(tam * sizeof(int));

        for(int i = 0; i < tam; i++)
            vetor[i] = i;
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

void max_heapify(int *v, int p, int n) {
    int f = (p * 2) + 1;

    if (f > n) return;
    
    if (v[f] > v[p] || (f + 1 <= n && v[f + 1] > v[p]) ) {
        if (f + 1 <= n && v[f + 1] > v[f])
            f = f + 1;

        swap(&v[p], &v[f]);

        max_heapify(v, f, n);
    }
}

void build_maxheap(int *v, int n) {
    int m = (int)n / 2;

    for (int i = m; i >= 0; i--)
        max_heapify(v, i, n);
}

void heap_sort(int *v, int n) {
    build_maxheap(v, n);

    while (n >= 1) {
        swap(&v[0], &v[n]);

        n--;
        max_heapify(v, 0, n);

    }
}

int particiona(int *v, int ini, int fim) {
	int pivo = ini; // ARBITRÁRIO
	int i = ini + 1;
	int j = fim;

	while(i <= j) {
		while(i <= fim && v[i] <= v[pivo]) i++; // Avança posição da esquerda
		while(v[j] > v[pivo]) j--; // Recua posição da direita
		// Troca esquerda e direita
		if(j >= i) {
            swap(&v[i++], &v[j--]);
		}	
	}
    swap(&v[pivo], &v[j]);
	
	return j;
}

void quickSort(int *v, int ini, int fim) {
    if (fim <= ini) return;
    // Separa os dados em 2 patições
    int pivo = particiona(v, ini, fim);  
    // Chamando recursivamente para as duas partições
    quickSort(v, ini, pivo - 1); 
    quickSort(v, pivo + 1, fim);
}

void criar_cabecalho(char *nome, bool normal) {
    FILE *arquivo = NULL;
    arquivo = fopen(nome, "w");
    if(normal)
        fprintf(arquivo, "Tamanho,Quick Sort,Heap Sort\n");
    else
        fprintf(arquivo, "Caso,Quick Sort,Heap Sort\n");
    fclose(arquivo);
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
    arquivo = fopen("Dados2.csv", "a");
    fprintf(arquivo, "%d,%lf,%lf\n",
            tam, media->tQuick, media->tHeap);
    fclose(arquivo);
}

void salvar_mp(char *caso, tempos_t *media) {
    FILE *arquivo = NULL;
    arquivo = fopen("DadosMP2.csv", "a");
    fprintf(arquivo, "%s,%lf,%lf\n", 
            caso, media->tQuick, media->tHeap);
    fclose(arquivo);
}

tempos_t comparar(int *vetor, int tam) {
    int *vetorCopiaQ = calloc(tam,  sizeof(int));
    int *vetorCopiaH = calloc(tam,  sizeof(int));

    for(int i = 0; i < tam; i++) {
        vetorCopiaQ[i] = vetor[i];
        vetorCopiaH[i] = vetor[i];
    }

    tempos_t tempo;
    clock_t c1, c2;

    c1 = clock();
    quickSort(vetorCopiaQ, 0, tam - 1);
    c2 = clock();
    
    tempo.tQuick = (c2 - c1) / (double) CLOCKS_PER_SEC;

    c1 = clock();
    heap_sort(vetorCopiaH, tam - 1);
    c2 = clock();

    tempo.tHeap = (c2 - c1) / (double) CLOCKS_PER_SEC;


    free(vetorCopiaQ);
    free(vetorCopiaH);

    printf("Quick: %lf Heap: %lf\n", tempo.tQuick, tempo.tHeap);

    return tempo;
}