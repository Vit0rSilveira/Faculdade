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
#include <assert.h>


enum comandos {ADICIONARMUSICA = 1, VISUALIZAR, PASSARMUSICA, VOLTARMUSICA, PARADA};

#define MAXMUSICAS 15

typedef struct {
    char *titulo;
    char *artista;
    int duracao;
} Musica;

typedef struct {
    char *nome;
    int qtdmusicas;
    Musica *musicaAtual;
    Musica *musica;
} Playlist;


char *receberNome();
void adicionarMusica(Playlist *play);
void exibirMusicas(Playlist *play);
void desalocarMemoria(Playlist *play);


int main() {
    Playlist minhaPlaylist;

    minhaPlaylist.nome = receberNome();
    
    minhaPlaylist.qtdmusicas = 0;
    minhaPlaylist.musicaAtual = NULL;
    minhaPlaylist.musica = NULL;

    int comando;
    do {
        scanf("%d", &comando);
        getchar();
        // A função getchar(), recebe o '\n', para que não haja problemas nas strings.
        
        if (comando == ADICIONARMUSICA) {
            if (minhaPlaylist.qtdmusicas == MAXMUSICAS)
                printf("Playlist cheia!\n");
            else 
                adicionarMusica(&minhaPlaylist);
        }
        else if (comando == VISUALIZAR)
            exibirMusicas(&minhaPlaylist);
        else if (comando == PASSARMUSICA)
            minhaPlaylist.musicaAtual += 1;
        else if (comando == VOLTARMUSICA)
            minhaPlaylist.musicaAtual -= 1;

    } while (comando != PARADA);

    desalocarMemoria(&minhaPlaylist);

    return 0;
}

/* Como está função faz alocações de memórias e para que não se perca os endereços alocacos
ela retorna um ponteiro, tal ponteiro aponta para o endereço inicial da memória alocada, assim
posso fazer a desalocação em outra parte do programa, pois há perca desses endereços. */
char *receberNome() {
    char *nome = NULL;
    int tamanhoNome = 0;
    
    while(1) {
        char caractereNome = getchar();
        
        nome = realloc(nome, (++tamanhoNome) * sizeof(char));
        assert(nome != NULL);

        nome[tamanhoNome - 1] = caractereNome;

        if (caractereNome == '\n' || caractereNome == '\r') {
            nome[tamanhoNome - 1] = '\0';
            break;
        }
    }    
    return nome;
}

void adicionarMusica(Playlist *play) {
    int indexMusicaAtual = play->musicaAtual - play->musica;

    play->musica = realloc(play->musica, (play->qtdmusicas + 1) * sizeof(Musica));
    
    play->musica[play->qtdmusicas].titulo = receberNome();
    play->musica[play->qtdmusicas].artista = receberNome();

    scanf("%d", &((*play).musica[play->qtdmusicas].duracao));

    printf("Musica %s de %s adicionada com sucesso.\n", play->musica[play->qtdmusicas].titulo, play->musica[play->qtdmusicas].artista);

    (play->qtdmusicas)++;

    play->musicaAtual = &(play->musica[indexMusicaAtual]);
}

void exibirMusicas(Playlist *play) {
    printf("---- Playlist: %s ----\n", play->nome);
    printf("Total de musicas: %d\n\n", play->qtdmusicas);
    for (int i = 0; i < play->qtdmusicas; i++) {
        if (play->musicaAtual == &play->musica[i])
            printf("=== NOW PLAYING ===\n");
            
        printf("(%d). '%s'\n", i + 1, play->musica[i].titulo);
        printf("Artista: %s\n", play->musica[i].artista);
        printf("Duracao: %d segundos\n\n", play->musica[i].duracao);
    }
}

void desalocarMemoria(Playlist *play) {
    free(play->nome);
    
    for (int i = 0; i < play->qtdmusicas; i++) {
        free(play->musica[i].titulo);
        free(play->musica[i].artista);
    }
    free((*play).musica);
}
