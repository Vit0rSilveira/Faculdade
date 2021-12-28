/**
 * Name: Vitor da Silveira Paula
 * 
 * Number: 10689651 
 */


#include <stdio.h>
#include <stdlib.h>


int *recieve_vector(int *cout);
void count_repeated(int *vector, int counter);


int main() {

    int counter = 0;
    int *vector = recieve_vector(&counter);
    
    count_repeated(vector, counter);

    free(vector);

    return 0;
}

int *recieve_vector(int *counter) {
    int *vector = NULL;
    int returnTmp = 0;

    do {
        vector = realloc(vector, ++(*counter) * sizeof(int));
        returnTmp = scanf("%d", &vector[*counter - 1]);

    } while(returnTmp != EOF);
    vector = realloc(vector, --(*counter) * sizeof(int));

    return vector;
}

/**
 * @brief This function, counts the repetead numbers, so Prints the number 
 * and his quantity.
 * 
 * @param vector Vector where is saved numbers.
 * @param counter Quantity of numbers saved.
 */
void count_repeated (int *vector, int counter) {
    for (int i = 0; i < counter; i++) {
        int counterTmp = 1;

        if (i == 0)
            printf("%d ", vector[i]);

        for (int j = i + 1; j < counter; j++) {
            if (vector[j] == vector[i]) {
                counterTmp++;
                vector[j] = vector[0];
            }
        }
        if (i == 0)
            printf("(%d)\n", counterTmp);
        else if (vector[i] != vector[0])
            printf("%d (%d)\n", vector[i], counterTmp);
    }
}
