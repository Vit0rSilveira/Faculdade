//Aula ICC1 Professor Tiago
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(){
    //Parte 1 - Tamanho os tipos de variáveis
    printf("Tamanho tipo vars:\n");
    printf("Char: %lu bytes(s)\n", sizeof(char));
    printf("int: %lu bytes(s)\n",sizeof(int));
    printf("float: %lu bytes(s)\n",sizeof(float));
    printf("double: %lu bytes(s)\n",sizeof(double));

    //Parte 2 - Modificadores
    printf("Tamanho dos modificadores\n");
    printf("Short int: %lu bytes(s)\n",sizeof(short int));
    printf("unsigned int: %lu bytes(s)\n",sizeof(unsigned int));
    printf("long int: %lu bytes(s)\n",sizeof(long int));
    printf("long long int: %lu bytes(s)\n",sizeof(long long int));

    printf("\n");

    //Parte 3 - Range
    printf("Range dos tipos de var:\n");
    printf("char: [%d, %d]\n",CHAR_MIN, CHAR_MAX);
    printf("int: [%d, %d]\n",INT_MIN, INT_MAX);
    printf("float: [%e , %e]\n",FLT_MIN, FLT_MAX);
    printf("double: [%e , %e]\n",DBL_MIN, DBL_MAX);

    //Parte 4 - Teste feito por mim
    char c =98;
    printf("%c\n",c);
    char a = 'b';
    printf("%d\n",a);
    return 0;
}