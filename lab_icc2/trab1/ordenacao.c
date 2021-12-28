/**
 * @file Orndenação aconchegante
 * @author Vitor da Silveira Paula - 10689651
 * 
 */


#include <stdio.h>
#include <stdlib.h>


typedef struct shell {
    double diameter;
    char *color;
    char *texture;
} shell_t;

shell_t *receive_shells();
void sort(shell_t **data, int qtd);
void print_shells(shell_t *data, int qtd);
void free_memory(shell_t *data, int qtd);


int main(int argc, char *argv[]) {
    int qtd;
    scanf("%d", &qtd);

    shell_t *data = receive_shells(qtd);
    sort(&data, qtd);
    print_shells(data, qtd);

    free_memory(data, qtd);

    return 0;
}

char *read_word() {
    char *name = NULL;
    char caractere = '\0';
    int cout = 0;

    while ((caractere = getchar()) == '\n' || caractere == ' ');
    if (caractere != EOF)
        ungetc(caractere, stdin);
    
    do {
        caractere = getchar();

        name = realloc(name, ++cout * sizeof(char));
        name[cout - 1] = caractere;

    } while (caractere != ' ' && caractere != '\n' && caractere != EOF);
    name[cout - 1] = '\0';

    return name;
}

/**
 * @brief allocate the memory needed for the save the informations from
 *  all shells.
 * 
 * @param qtd number os shells.
 * @return shell_t* structure with reserved memory.
 */
shell_t *alloc_memory(int qtd) {
    shell_t *tmp = malloc(qtd * sizeof(shell_t));

    return tmp;
}

/**
 * @brief Receive the informations about shells.
 * 
 * @param qtd 
 * @return shell_t* structure with saved informations.
 */
shell_t *receive_shells(int qtd) {
    shell_t *data = alloc_memory(qtd);

    for(int i = 0; i < qtd; i++) {
        scanf(" %lf", &data[i].diameter);
        data[i].color = read_word();
        data[i].texture = read_word();
    }

    return data;
}

/**
 * @brief sort te shells according to diameter.
 * 
 * @param data strucuture with all data.
 * @param qtd 
 */
void sort(shell_t **data, int qtd) {
    int d = qtd / 2;
    while (d > 0) {
        for(int i = 0; i < d; i++) {
            for(int j = d + i; j < qtd; j += d) {
                double chave1 = (*data)[j].diameter;
                
                shell_t tmp = (*data)[j];

                int k = j - d;
                
                while((k >= 0) && (*data)[k].diameter > chave1) {
                    (*data)[k + d] = (*data)[k];

                    k -= d;
                }
                (*data)[k + d] = tmp;
            }
            
        }
        d /= 2;
    }
}

void print_shells(shell_t *data, int qtd) {
    for(int i = 0; i < qtd; i++)   
        printf("%.3lf %s %s\n", data[i].diameter, data[i].color, 
                data[i].texture);
}

void free_memory(shell_t *data, int qtd) {
    for(int i = 0; i < qtd; i++) {
        free(data[i].color);
        free(data[i].texture);
    }
    free(data);
}
