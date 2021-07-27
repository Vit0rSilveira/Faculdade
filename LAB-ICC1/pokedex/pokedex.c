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


enum comandos {PARAR, CADASTRO, ADDATAQUE, PRINTPOKEMON, PRINTATAQUE};


typedef struct {
    char nomeAtaque[21];
    int poderBase;
    float acuracia;
    char classe;
} ataque_t;

typedef struct {
    int hp;
    int ataque;
    int defesa;
    int ataqueEspecial;
    int defesaEspecial;
    int velocidade;
} status_t;

typedef struct {
    char nome[51];
    char tipoPrimario[21];
    char tipoSecundario[21];
    status_t status;
    ataque_t ataques[4];
} pokemon_t;

void adicionarPokemon(pokemon_t **pokemon, int *qtdPokemon);
void adicionarAtaque(pokemon_t *pokemon);
void imprimirPokemon(pokemon_t *pokemon);
void imprimirAtaque(pokemon_t *pokemon);

int main() {
    pokemon_t *meuPokedex = NULL;

    int comando, qtdPokemon = 0;
    do {
        scanf("%d", &comando);

        switch (comando) {
            case CADASTRO:
                adicionarPokemon(&meuPokedex, &qtdPokemon);
                break;
            case ADDATAQUE:
                adicionarAtaque(meuPokedex);
                break;
            case PRINTPOKEMON:
                imprimirPokemon(meuPokedex);
                break;
            case PRINTATAQUE:
                imprimirAtaque(meuPokedex);
                break;
        }
    } while(comando != PARAR);

    free(meuPokedex);

    return 0;
}

void adicionarPokemon(pokemon_t **pokemon, int *qtdPokemon) {
    *pokemon = realloc(*pokemon, ++(*qtdPokemon) * sizeof(pokemon_t));

    scanf("%s", (*pokemon)[(*qtdPokemon) - 1].nome);
    scanf("%s", (*pokemon)[(*qtdPokemon) - 1].tipoPrimario);
    scanf("%s", (*pokemon)[(*qtdPokemon) - 1].tipoSecundario);
    scanf("%d", &(*pokemon)[(*qtdPokemon) - 1].status.hp);
    scanf("%d", &(*pokemon)[(*qtdPokemon) - 1].status.ataque);
    scanf("%d", &(*pokemon)[(*qtdPokemon) - 1].status.defesa);
    scanf("%d", &(*pokemon)[(*qtdPokemon) - 1].status.ataqueEspecial);
    scanf("%d", &(*pokemon)[(*qtdPokemon) - 1].status.defesaEspecial);
    scanf("%d", &(*pokemon)[(*qtdPokemon) - 1].status.velocidade);
}

void adicionarAtaque(pokemon_t *pokemon) {
    int indicePokemon, indiceAtaque;
    scanf("%d %d", &indicePokemon, &indiceAtaque);

    scanf(" %s", pokemon[indicePokemon].ataques[indiceAtaque].nomeAtaque);
    scanf("%d", &pokemon[indicePokemon].ataques[indiceAtaque].poderBase);
    scanf("%f", &pokemon[indicePokemon].ataques[indiceAtaque].acuracia);
    scanf(" %c", &pokemon[indicePokemon].ataques[indiceAtaque].classe);
}

void imprimirPokemon(pokemon_t *pokemon) {
    int indicePokemon;
    scanf("%d", &indicePokemon);

    printf("Nome do Pokemon: %s\n", pokemon[indicePokemon].nome);
    printf("Tipo primario: %s\n", pokemon[indicePokemon].tipoPrimario);
    printf("Tipo secundario: %s\n", pokemon[indicePokemon].tipoSecundario);
    printf("Status:\n");
    printf("\tHP: %d\n", pokemon[indicePokemon].status.hp);
    printf("\tAtaque: %d\n", pokemon[indicePokemon].status.ataque);
    printf("\tDefesa: %d\n", pokemon[indicePokemon].status.defesa);
    printf("\tAtaque Especial: %d\n", pokemon[indicePokemon].status.ataqueEspecial);
    printf("\tDefesa Especial: %d\n", pokemon[indicePokemon].status.defesaEspecial);
    printf("\tVelocidade: %d\n\n", pokemon[indicePokemon].status.velocidade);
}

void imprimirAtaque(pokemon_t *pokemon) {
    int indicePokemon, indiceAtaque;
    scanf("%d %d", &indicePokemon, &indiceAtaque);

    printf("Nome do Ataque: %s\n", pokemon[indicePokemon].ataques[indiceAtaque].nomeAtaque);
    printf("Poder base: %d\n", pokemon[indicePokemon].ataques[indiceAtaque].poderBase);
    printf("Acuracia: %f\n", pokemon[indicePokemon].ataques[indiceAtaque].acuracia);
    printf("Classe: %c\n\n", pokemon[indicePokemon].ataques[indiceAtaque].classe);
}
