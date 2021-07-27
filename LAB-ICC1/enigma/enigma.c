// Vitor da Silveira Paula - 10689651

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{

    int rotor1[26], rotor2[26], rotor3[26];

    scanf("%*[^\r\n]s"); // Ignora tudo até o final da linha

    for (int i = 0; i < 26; i++) {
        scanf(" %d", &rotor1[i]);
    }

    for (int i = 0; i < 26; i++) {
        scanf(" %d", &rotor2[i]);
    }

    for (int i = 0; i < 26; i++) {
        scanf(" %d", &rotor3[i]);
    }
    scanf("%*[\r\n]s"); // Ignora o pula linha

    char mensagem;
    int saida;
    int rotacao = 0;
    int rotacao2 = 0;
    int rotacao3 = 0;
    scanf("%*[^\r\n]s"); // Ignora tudo até o final da linha
    scanf("%*[\r\n]s");  // Ignora o pula linha
    while (1) {

        saida = scanf("%c", &mensagem);

        if (saida == EOF) {
            break;
        }


        /* Verificação se meus carateres são maiúsculo ou minúsculo.
           Decodificação caracter por caractere */
        int codMensagem;
        
        if (isupper(mensagem)) {

            codMensagem = rotor3[(rotor2[(rotor1[(mensagem - 'A' + rotacao) % 26] + rotacao2) % 26] + rotacao3) % 26];
            rotacao++;
            if (rotacao == 26) {
                rotacao = 0;
                rotacao2++;  
            }
            if (rotacao2 == 26) {
                rotacao2 = 0;
                rotacao3++;
            }
            printf("%c", codMensagem + 'A'); 
        }
        else if (islower(mensagem)) {
            codMensagem = rotor3[(rotor2[(rotor1[(mensagem - 'a' + rotacao) % 26] + rotacao2) % 26] + rotacao3) % 26];
            rotacao++;
            if (rotacao == 26) {
                rotacao = 0;
                rotacao2++;
            }
            if (rotacao2 == 26) {
                rotacao2 = 0;
                rotacao3++;
            }
            printf("%c", codMensagem + 'a'); 
        }
        else {
            printf("%c", mensagem);
        }
    }

    return 0;
}