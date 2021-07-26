#include <stdio.h>
#include <stdlib.h>

int main() {

    int tamanhoMensagem;
    int mensagem;
    char teclado[49];

    for (int i = 0; i < 49; i++) {
        scanf("%c", &teclado[i]);
        getchar(); // scanf é meio burro na hora de ler, ele considera o espaço como caracter
    }              // getchar le um caracter da entrada padrão, nesse caso seriam os espaços.

    scanf("%d", &tamanhoMensagem);

    for (int i = 0; i < tamanhoMensagem; i++) {
        scanf("%d", &mensagem);
        
        if (teclado[mensagem] == '_') {
            printf(" ");
        }
        else if (teclado[mensagem] == 'E') {
            printf("\n");
        }
        else {
            printf("%c", teclado[mensagem]);
        }
        
    }

    return 0;
}