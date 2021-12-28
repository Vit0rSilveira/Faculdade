#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


/**
 * @brief This structs has the two limits, the first limit is the superior limit
 *  of the first recursive call, and the second limit is the inferior limit
 * of the second recursive call.
 * 
 */
typedef struct limit {
    int firstLimit;
    int secondLimit;
} limit_t;

#define PIVO_MEDIAN '1'
#define PIVO_RANDOM '2'

void insertion_sort(int *vector, int begin, int end);
void quick_sort(int *v, int begin, int end, int (*eep)(int*, int, int));
int pivo_random(int *v, int begin, int end);
int pivo_median(int *v, int begin, int end);
int *receive_vector(int size);
void show_vector(int *v, int size);


int main(int argc, char *agrv[]) {
    int size;
    char method;
    scanf(" %d %c", &size, &method);

    int *vector = receive_vector(size);
    if (method == PIVO_MEDIAN) {
        quick_sort(vector, 0, size - 1, pivo_median);
    }
    else if (method == PIVO_RANDOM) {
        srand(42);
        quick_sort(vector, 0, size - 1, pivo_random);
    }

    show_vector(vector, size);

    free(vector);
    return EXIT_SUCCESS;
}

/**
 * @brief This function sorts a part of the vector.
 * 
 * @param vector Vector to be ordered
 * @param begin First value to be ordered
 * @param end Last value to be ordered
 */
void insertion_sort(int *vector, int begin, int end) {
    for (int i = begin + 1; i <= end; i++) {
        int key = vector[i];
        int j = i - 1;

        while (j >= begin && vector[j] > key) {
            vector[j + 1] = vector[j];
            j--;
        }
        vector[j + 1] = key;
    }
}

void show_vector(int *v, int size) {
    for (int i = 0; i < size; i++)
        printf("%d\n", v[i]);
}

int *receive_vector(int size) {
    int *v = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
        scanf(" %d", &v[i]);

    return v;
}

/**
 * @brief This function chooses de position of the pivot according a random
 * 
 * @param v Vector to be ordered
 * @param begin Begin the vector
 * @param end Last the Vector
 * @return int The position drawn according the value of the begin vector
 */
int pivo_random(int *v, int begin, int end) {
    return (rand() % (end - begin + 1)) + begin;
}

void swap (int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * @brief This function selects the First, the center e the last value the
 * vector and determines the median value.
 * 
 * @param v Vector to be ordered
 * @param begin Begin the vector
 * @param end Last the Vector
 * @return int The position of the median value
 */
int pivo_median(int *v, int begin, int end) {
    int center = (begin + end + 1) / 2;

    if (v[begin] > v[center] && v[begin] < v[end])
        return begin;
    else if (v[begin] > v[end] && v[begin] < v[center])
        return begin;
    else if (v[center] > v[begin] && v[center] < v[end])
        return center;
    else if (v[center] > v[end] && v[center] < v[begin])
        return center;
    else if (v[end] > v[begin] && v[end] < v[center])
        return end;
    else
        return end;
    
    return -1;
}

/**
 * @brief This function selects the pivot and puts it in the right place in the
 * vector, and determines the limits of the new recursive call.
 * 
 * 
 * @param v Vector to be ordered
 * @param begin Begin the vector
 * @param end Last the Vector
 * @param eep Function that change the pivot.
 * @return limit_t The struct with the limits for the new ordering
 */
limit_t partition(int *v, int begin, int end, int (*eep)(int*, int, int)) {
    int pivot = eep(v, begin, end);
    swap(&v[pivot], &v[end]);
    pivot = end;

    limit_t l;
    l.firstLimit = begin;
    l.secondLimit = begin;
    int endCenter = end - 1;

    while (l.secondLimit <= endCenter) {
        /*  If the second limit value is less than the pivot value, the second
             limit exchages values with the first.*/
        if (v[l.secondLimit] < v[pivot])
            swap(&v[l.secondLimit++], &v[l.firstLimit++]);
            /*  If the pivot value is less than the second limit value the 
                second limit exchanges values with the end. */
        else if (v[l.secondLimit] > v[pivot])
            swap(&v[l.secondLimit], &v[endCenter--]);
        else
            l.secondLimit++;
    }

    swap(&v[l.secondLimit], &v[pivot]);

    return l;
}

/**
 * @brief This function executes 3 way Quick Sort. And if the size of the
 * partition is smaller than or equal to 10 sorts with the Insertion Sort 
 * algorithm.
 * 
 * @param v Vector to be ordered
 * @param begin Begin the vector
 * @param end Last the Vector
 * @param eep Function that change the pivot.
 */
void quick_sort(int *v, int begin, int end, int (*eep)(int*, int, int)) {
    if (end - begin + 1 <= 10) {
        insertion_sort(v, begin, end);
        return;
    }

    limit_t l =  partition(v, begin, end, eep);

    quick_sort(v, begin, l.firstLimit - 1, eep);
    quick_sort(v, l.secondLimit + 1, end, eep);
}