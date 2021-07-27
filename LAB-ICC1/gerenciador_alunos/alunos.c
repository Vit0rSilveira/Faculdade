/*---------------------------------------------------------------------- 
                Universidade de São Paulo
        Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PARADA -1


typedef struct {
    int identificador;
    char *nome;
    char *curso;
    int idade;
} estudantes;


estudantes *receberAlunos(int *qtdAlunos);
void consultarAlunos(estudantes *alunos, int qtdAlunos);
void consultarCurso(estudantes *alunos, int qtdAlunos);
void mostrarAlunos(estudantes *alunos, int qtdAlunos);


int main() {
    int qtdAlunos;
    estudantes *alunos = receberAlunos(&qtdAlunos);

    int operacao;
    do {
        scanf("%d", &operacao);

        switch (operacao) {
            case 1:
                consultarAlunos(alunos, qtdAlunos);
                break;
            case 2:
                consultarCurso(alunos, qtdAlunos);
                break;
            case 3:
                mostrarAlunos(alunos, qtdAlunos);
                break;
        }
    }  while(operacao != PARADA);
    
    for (int i = 0; i < qtdAlunos; i++) {
        free(alunos[i].nome);
        free(alunos[i].curso);
    }
    free(alunos);

    return 0;
}

char *readLine() {
    char *linha = NULL;
    char caractere = '\0';
    int qtdCaractere = 0;

    while ((caractere = getchar()) == '\n');
    if (caractere != EOF)
        ungetc(caractere, stdin);

    do {
        caractere = getchar();
        linha = realloc(linha, (qtdCaractere + 1) * sizeof(char));

        linha[qtdCaractere++] = caractere;

    } while (caractere != '\n');
    linha[qtdCaractere - 1] = '\0';

    return linha;
}

estudantes *receberAlunos(int *qtdAlunos) {
    estudantes *alunos = NULL;
    *qtdAlunos = 0;
    int identificar;

    while(1) {
        scanf("%d", &identificar);
        if (identificar == PARADA) {
            break;
        }
        else {
            alunos = realloc(alunos, (++(*qtdAlunos)) * sizeof(estudantes));

            alunos[(*qtdAlunos) - 1].identificador = identificar;
            alunos[(*qtdAlunos) - 1].nome = readLine();
            alunos[(*qtdAlunos) - 1].curso = readLine();
            scanf("%d", &alunos[(*qtdAlunos) - 1].idade);
        }
    }

    return alunos;
}

void mostrarInformacao(estudantes alunos) {
    printf("Nome: %s\n", alunos.nome);
    printf("Curso: %s\n", alunos.curso);
    printf("N USP: %d\n", alunos.identificador);
    printf("IDADE: %d\n\n", alunos.idade);
}

void mostrarAlunos(estudantes *alunos, int qtdAlunos) {
    for (int i = 0; i < qtdAlunos; i++) {
       mostrarInformacao(alunos[i]);
    }
}

void consultarAlunos(estudantes *alunos, int qtdAlunos) {
    int numConsulta;
    scanf(" %d", &numConsulta);
    for (int i = 0; i < qtdAlunos; i++) {

        if (numConsulta == alunos[i].identificador) {
            mostrarInformacao(alunos[i]);
            return;
        }
    }
    printf("Aluno nao cadastrado\n");
}

void consultarCurso(estudantes *alunos, int qtdAlunos) {
    char *curso = readLine();
    for (int i = 0; i < qtdAlunos; i++) {

        if (strcmp(curso, alunos[i].curso) == 0) {
            mostrarInformacao(alunos[i]);
        }
    }
    free(curso);
    return;
}
