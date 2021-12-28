// Contagem de operações e análise de recorrência das funções de ordenação.
// Não será levado em cosideração as operações do for.
// Sera levado em consideração as operações aritméticas e comparações.
// a - aritméticas.
// c - comparação.

void bubble_sort(int *vetor, int tamanho) { // n = Tamanho.
    for(int i = tamanho - 1; i > 0; i--) {
        for(int j = 0; j < i; j++) {
            if(vetor[j] > vetor[j + 1]) { // c + a
                int aux = vetor[j];
                vetor[j] = vetor[j + 1]; // a
                vetor[j + 1] = aux; // a
            }
        }
    }
}

//F(n) =  (c + 3a) * sum_(k = 1)^(n - 1) n - k
// sum_(k = 1)^(n - 1) n - k -- PA
// Soma PA: n(a1 + an)/2 --> [(n - 1)(n - 1 + n - (n - 1))] / 2 -- > (n*n - n) / 2

//F(n) = (3a + c)  * (n^2 - n) / 2
//F(n) = [(3a + c) * (n^2 - n)] / 2
/* Se a e C valesse 1:
    F(n) =F(n) 2n^2 - 2
*/


void insertion_sort(int *vetor, int tamanho) { // n = Tamanho.
    for(int i = 1; i < tamanho; i++) {
        int chave = vetor[i];
        int j = i - 1;                        // a

        while((j >= 0) && vetor[j] > chave) { //2c sum_(k = 1)^(n - 1) k
            vetor[j + 1] = vetor[j];                //a
            j--;                                    //a
        }
        vetor[j + 1] = chave;               //a
    }
}

//F(n) =  (2a) * n + sum_(k = 2)^(n - 3) n - k
// sum_(k = 2)^(n - 3) n - k -- PA
// Soma PA: n(a1 + an)/2 --> [(n - 2)(n - 2 + n - (n - 3))] / 2 -- > (n*n - n - 2) / 2

//F(n) = [(n^2 - n - 2 ) / 2] + 2a * n
/* Se a e C valesse 1:
    F(n) = [(n^2 - n - 2 ) / 2] + 2n
*/

void  merge(int *vetor, int ini, int m, int fim) { 
    int size = fim - ini + 1;                   //2a
    int *copia = malloc(size * sizeof(int));    //a

    int p1 = ini;
    int p2 = m + 1;                             //a

    for(int i = 0; i < size; i++) {
        if (p1 <= m && p2 <= fim) {             //2c * n
            if(vetor[p1] > vetor[p2])           //c * n 
                copia[i] = vetor[p2++];
            else
                copia[i] = vetor[p1++];         //a * n
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
        vetor[j++] = copia[i];                  //a * n
    
    free(copia);
}
//F(n) = 4a + 4n(2a + 3c)


void merge_sort(int *vetor, int ini, int fim) {
    if (fim <= ini) return;   // c

    int m = (fim + ini) / 2;  // 2a

    merge_sort(vetor, ini, m); // ms(n/2)
    merge_sort(vetor, m + 1, fim); // ms(n/2)

    merge(vetor, ini, m, fim); // merge(n)

}

//F(n) = 6a + c + 4n(2a + 3c) + 2ms(n/2)
//F(n/2) = 6a + c + 4n/2(2a + 3c) + 2ms(n/4)
//F(n/4) = 6a + c + 4n/4(2a + 3c) + 2ms(n/8)


//F(n) = 6a + c + 4n(2a + 3c) + 2*(6a + c + 4n/2(2a + 3c) + 2*(6a + c + 4n/4(2a + 3c) + 2ms(n/8)))
//F(n) = 6a + 12a + 24a + c + 2c + 4c + 4kn*(2a + 3c)  + 2^kms(n/2^k)
//F(n) = 6a sum_(i = 0)(k - 1) 2^i + c sum_(i = 0)^(k - 1) 2^i + 4kn*(2a + 3c) + 2^kms(n/2^k)
//F(n) = (6a + c) sum_(i = 0)(k - 1) 2^i + 4nk*(2a + 3c) + 2^kms(n/2^k)

// n/2^k --> k = log_2 n

// sum_(i = 0)(k - 1) 2^i --> pg
// Soma = a1*(1 - q^n) / (1 - q) --> 1(2^(k - 1) - 1)

//F(n) = (6a + c) * (2^(log_2 n - 1) - 1) + 4n(log_2 n)*(2a + 3c) + 2^(log_2 n)
//F(n) = (6a + c) * ((n/2) - 1) + 4n(log_2 n)*(2a + 3c) + 2^(log_2 n)

/* Se a e C valesse 1:
    F(n) = 7n/2 - 7 + 20n(log_2 n) + n
    F(n) = 20n(log_2 n) + 9n/2 - 7
*/