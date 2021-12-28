/**
 * @file main.c
 * @author Vitor da Silveira Paula Nº 10689651
 * @brief Trabalho 02 - Compressão de áudio.
 * SCC0201 - Introdução à Ciência da Computação 2.
 * @version last version.
 * @date 14 de outubro.
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <complex.h>


struct wav {
    char *fName;
    unsigned char *data;
    int length;
};

struct coeficientes {
    double complex coef;
    int index;
};

typedef struct wav wav_t;
typedef struct coeficientes coef_t;


char *read_name();
unsigned char *read_wav(wav_t *wavData);
coef_t *begin_coef(unsigned char *audio, int length);
void merge_sort(coef_t *vetor, int ini, int fim);
void put_zero(coef_t *coef, int length, int T);
void return_position(coef_t *coef, int length);
void print_info(int length ,coef_t *coef, int T);
void free_memory(wav_t *wavData, coef_t *mag);
void TIF(wav_t *data, coef_t *coef);
void save_file(wav_t *data);


int main(int argc, char *argv[]) {
    wav_t wavData;
    wavData.fName = read_name();
    wavData.data = read_wav(&wavData);

    coef_t *coef = begin_coef(wavData.data, wavData.length);
    merge_sort(coef, 0, wavData.length - 1);

    int T;
    scanf(" %d", &T);
    print_info(wavData.length, coef, T);
    put_zero(coef, wavData.length, T);

    return_position(coef, wavData.length);

    TIF(&wavData, coef);

    save_file(&wavData);

    free_memory(&wavData, coef);

    return 0;
}

/**
 * @brief Calculate the magnitude os the complex number.
 * 
 * @param number Complex number.
 * @return double Magnitude of the number
 */
double magnitude(double complex number) {
    double real = creal(number);
    double img = cimag(number);

    double mag = sqrt(pow(real,2) + pow(img, 2));

    return mag;
}

/**
 * @brief Count the amount number less or equal to zero, both in the real and in
 * the imaginary part
 * 
 * @param coef 
 * @param length 
 * @return int Counted quantity.
 */
int count_zeros(coef_t *coef, int length) {
    int s = 0;

    for(int i = 0; i < length; i++) {
        if(creal(coef[i].coef) <= 0 && cimag(coef[i].coef) <= 0)
            s++;
    }

    return s;
}

/**
 * @brief Show of the requested informations.
 * 
 * @param length 
 * @param coef 
 * @param T 
 */
void print_info(int length, coef_t *coef, int T) {
    printf("%d\n", length);
    printf("%d\n", count_zeros(coef, length));

    for(int i = 0; i < T; i++)
        printf("%d\n", (int)magnitude(coef[i].coef));
}

void merge(coef_t *vetor, int ini, int meio, int fim) {
    int size = fim - ini + 1;

    coef_t *copy = malloc(size * sizeof(coef_t));
    assert(copy != NULL);

    int p1 = ini;
    int p2 = meio + 1;

    for(int i = 0; i < size; i++) {
        if(p1 <= meio && p2 <= fim) {
            if(magnitude(vetor[p1].coef) < magnitude(vetor[p2].coef))
                copy[i] = vetor[p2++];
            else
                copy[i] = vetor[p1++];
        }
        else if(p1 > meio)
            copy[i] = vetor[p2++];
        else
            copy[i] = vetor[p1++];
    }

    for(int i = 0, j = ini; i < size; i++, j++)
        vetor[j] = copy[i];

    free(copy);
}

void merge_sort(coef_t *vetor, int ini, int fim) {
    if(fim <= ini) return;

    int meio = (fim + ini) / 2;
    merge_sort(vetor, ini, meio);
    merge_sort(vetor, meio + 1, fim);

    merge(vetor, ini, meio, fim);
}

/**
 * @brief Reserve the memory for the coefficients that they are complex double 
 * and after, do computing the coefficients with the discrete Fourier transform
 * and save de original index of each coefficient.
 * 
 * @param audio 
 * @param length 
 * @return coef_t* Array of the structs with the informations about coefficients.
 */
coef_t *begin_coef(unsigned char *audio, int length) {
    coef_t *coef = calloc(length, sizeof(coef_t));
    assert(coef != NULL);

    for (int k = 0; k < length; k++) {
        for (int n = 0; n < length; n++) {
            coef[k].coef += audio[n] * cexp((-2.0 * M_PI * (((k+1) * n * 1.0) / (length * 1.0))) * _Complex_I);
        }
        coef[k].index = k;
    }
    return coef;
}

int is_endLine(char c) {
    if(c == '\r' || c == '\n')
        return 1;

    return 0;
}

char *read_name() {
    char *name = NULL;
    int count = 0;

    char c = getchar();
    while(is_endLine(c));
    if(c != EOF)
        ungetc(c, stdin);

    do {
        c = getchar();
        name = realloc(name, ++count * sizeof(char));
        assert(name != NULL);

        name[count - 1] = c;


    } while(!is_endLine(c) && c != EOF);
    name[count - 1] = '\0';

    return name;
}

unsigned char *read_wav(wav_t *wavData) {
    FILE *fp = fopen(wavData->fName, "rb");
    unsigned char buf4[4];

    fseek(fp, 40, SEEK_SET);
    fread(buf4, sizeof(buf4), 1, fp);
    wavData->length = buf4[0] | buf4[1]<<8 | buf4[2]<<16 | buf4[3]<<24;

    unsigned char *data = malloc(sizeof(*data) * (wavData->length));
    
    int i = 0;
    while (i < wavData->length) {
        fread(&data[i++], sizeof(unsigned char), 1, fp);
    }
    fclose(fp);

    return data;
}

void put_zero(coef_t *coef, int length, int T) {
    for(int i = T; i < length; i++) 
        coef[i].coef = 0;
}

/**
 * @brief Return the coefficients for the position before the sort.
 * 
 * @param coef 
 * @param length 
 */
void return_position(coef_t *coef, int length) {
    coef_t *copy = malloc(length * sizeof(coef_t));

    for(int i = 0; i < length; i++) {
        for(int j = 0; j < length; j++) {
            if(i == coef[j].index) {
                copy[i] = coef[j];
            }
        }
    }

    for(int i = 0; i < length; i++) {
        coef[i] = copy[i];
    }

    free(copy);
}

/**
 * @brief Do computing inverse transform Fourrier and save the real number, and
 * replaces the wav data with the compress audio
 * 
 * @param data 
 * @param coef 
 */
void TIF(wav_t *data, coef_t *coef) {
    for(int i = 0; i < data->length; i++) {
        double complex tmp = 0;
        for(int j = 0; j < data->length; j++)
            tmp += coef[j].coef * cexp((2.0 * M_PI *  (((j + 1) * i * 1.0) / (data->length * 1.0))) * _Complex_I);

        tmp /= data->length;

        data->data[i] = (unsigned char)creal(tmp);
    }
}

/**
 * @brief Save the new audio to other file wav
 * 
 * @param data 
 * @param coef 
 */
void save_file(wav_t *data) {
    FILE *p = fopen(data->fName, "rb");
    if(p == NULL)
        printf("Ih, deu ruim\n");

    FILE *p2 = fopen("newAudio.wav", "wb");
    if(p2 == NULL)
        printf("Ih, deu ruim\n");

    unsigned char buffer[44];
    fread(buffer, sizeof(unsigned char), 44, p);

    fwrite(buffer, 1, 44, p2);
    fwrite(data->data, sizeof(unsigned char), data->length, p2);

    fclose(p);
    fclose(p2);
}

void free_memory(wav_t *wavData, coef_t *coef) {
    free(wavData->fName);
    free(wavData->data);
    free(coef);
}