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


enum comandos {
    CMD_ADICIONAR_MUSICA = 1,
    CMD_VISUALIZAR,
    CMD_PASSAR_MUSICA,
    CMD_VOLTAR_MUSICA,
    CMD_SALVAR_PLAYLIST,
    CMD_CARREGAR_PLAYLIST,
    CMD_PARADA
};

#define MAX_MUSICAS 15

typedef struct {
    char *titulo;
    char *artista;
    int duracao;
} musica_t;

typedef struct {
    char *nome;
    int qtdmusicas;
    musica_t *musicaAtual;
    musica_t *musica;
} playlist_t;


char *receberNome();
void adicionarMusica(playlist_t *play);
void exibirMusicas(playlist_t *play);
void liberarPlaylist(playlist_t *play);
void salvarPlaylist(playlist_t play);
int carregarPlaylist(playlist_t *play);
void binaryToNum(char *binFilename);


int main() {
    playlist_t minhaPlaylist;

    minhaPlaylist.nome = receberNome();
    
    minhaPlaylist.qtdmusicas = 0;
    minhaPlaylist.musicaAtual = NULL;
    minhaPlaylist.musica = NULL;

    int comando, ERRO = 0;
    do {
        scanf("%d", &comando);

        switch (comando) {
            case CMD_ADICIONAR_MUSICA:
                if (minhaPlaylist.qtdmusicas == MAX_MUSICAS)
                    printf("Playlist cheia!\n");
                else 
                    adicionarMusica(&minhaPlaylist);
                break;
            case CMD_VISUALIZAR:
                exibirMusicas(&minhaPlaylist);
                break;
            case CMD_PASSAR_MUSICA:
                minhaPlaylist.musicaAtual += 1;
                break;
            case CMD_VOLTAR_MUSICA:
                minhaPlaylist.musicaAtual -= 1;
                break;
            case CMD_SALVAR_PLAYLIST:
                salvarPlaylist(minhaPlaylist);
                break;
            case CMD_CARREGAR_PLAYLIST:
                ERRO = carregarPlaylist(&minhaPlaylist);
                break;
        }
    } while (comando != CMD_PARADA && ERRO == 0);

    liberarPlaylist(&minhaPlaylist);

    return 0;
}

char *receberNome() {
    char *nome = NULL;
    int tamanhoNome = 0;
    
    char caractereNome;
    while ((caractereNome = getchar()) == '\n');
    if (caractereNome != EOF)
        ungetc(caractereNome, stdin);

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

void adicionarMusica(playlist_t *play) {
    int indexMusicaAtual = play->musicaAtual - play->musica;

    play->musica = realloc(play->musica, (play->qtdmusicas + 1) * sizeof(musica_t));
    
    play->musica[play->qtdmusicas].titulo = receberNome();
    play->musica[play->qtdmusicas].artista = receberNome();

    scanf("%d", &((*play).musica[play->qtdmusicas].duracao));

    printf("Musica %s de %s adicionada com sucesso.\n", play->musica[play->qtdmusicas].titulo,
                                                        play->musica[play->qtdmusicas].artista);

    (play->qtdmusicas)++;

    play->musicaAtual = &(play->musica[indexMusicaAtual]);
}

void exibirMusicas(playlist_t *play) {
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

void salvarPlaylist(playlist_t play) {
    char *nomeArquivo = receberNome();

    FILE *arquivo = fopen(nomeArquivo, "wb");

    int tamanhoNome = strlen(play.nome);
    fwrite(&tamanhoNome, sizeof(int), 1, arquivo);

    fwrite(play.nome, sizeof(char), tamanhoNome, arquivo);

    fwrite(&play.qtdmusicas, sizeof(int), 1, arquivo);

    for (int i = 0; i < play.qtdmusicas; i++) {
        int tamanhoTitulo = strlen(play.musica[i].titulo);

        fwrite(&tamanhoTitulo, sizeof(int), 1, arquivo);
        fwrite(play.musica[i].titulo, sizeof(char), tamanhoTitulo, arquivo);

        int tamanhoNomeArtista = strlen(play.musica[i].artista);

        fwrite(&tamanhoNomeArtista, sizeof(int), 1, arquivo);
        fwrite(play.musica[i].artista, sizeof(char), tamanhoNomeArtista, arquivo);

        fwrite(&play.musica[i].duracao, sizeof(int), 1, arquivo);
    }
    fclose(arquivo);

    printf("Playlist %s salva com sucesso.\n", nomeArquivo);

    binaryToNum(nomeArquivo);

    free(nomeArquivo);
}

/* Como eu irei salvar uma nova playlist que eu ainda não sei o tamanho, eu desaloco
os espaços de memória que já estavam alocados, para evitar não ter problema.*/
int carregarPlaylist(playlist_t *play) {

    char *nomeArquivo = receberNome();

    FILE *arquivoLeitura = fopen(nomeArquivo, "rb");
    if (arquivoLeitura == NULL) {
        printf("Arquivo %s nao existe.\n", nomeArquivo);
        free(nomeArquivo);
        return 1;
    }
    liberarPlaylist(play);

    int tamanhoNome;
    fread(&tamanhoNome, sizeof(int), 1, arquivoLeitura);
    
    play->nome = malloc((tamanhoNome + 1) * sizeof(char));
    fread(play->nome, sizeof(char), tamanhoNome, arquivoLeitura);
    play->nome[tamanhoNome] = '\0';

    fread(&play->qtdmusicas, sizeof(int), 1, arquivoLeitura);
    play->musica = malloc( play->qtdmusicas * sizeof(musica_t));

    for (int i = 0; i < play->qtdmusicas; i++) {
        int tamanhoTitulo;
        fread(&tamanhoTitulo, sizeof(int), 1, arquivoLeitura);
        play->musica[i].titulo = malloc((tamanhoTitulo + 1) * sizeof(char));
        fread(play->musica[i].titulo, sizeof(char), tamanhoTitulo, arquivoLeitura);
        play->musica[i].titulo[tamanhoTitulo] = '\0';

        int tamanhoNomeArtista;
        fread(&tamanhoNomeArtista, sizeof(int), 1, arquivoLeitura);
        play->musica[i].artista = malloc((tamanhoNomeArtista + 1)* sizeof(char));
        fread(play->musica[i].artista, sizeof(char), tamanhoNomeArtista, arquivoLeitura);
        play->musica[i].artista[tamanhoNomeArtista] = '\0';

        fread(&play->musica[i].duracao, sizeof(int), 1, arquivoLeitura);
    }
    fclose(arquivoLeitura);

    printf("Playlist %s carregada com sucesso.\n", nomeArquivo);
    play->musicaAtual = &play->musica[0];

    binaryToNum(nomeArquivo);

    free(nomeArquivo);

    return 0;
}

void binaryToNum(char *binFilename) {
    FILE *fp = fopen(binFilename, "rb");

    double binValue = 0;
    double accumulator = 0.01;
    char ch;
    while (fread(&ch, sizeof(char), 1, fp)) {
        binValue += (double) ch * accumulator;
        accumulator += 0.01;
    }

    fclose(fp);
    printf("%lf\n", binValue);
}

void liberarPlaylist(playlist_t *play) {
    free(play->nome);
    
    for (int i = 0; i < play->qtdmusicas; i++) {
        free(play->musica[i].titulo);
        free(play->musica[i].artista);
    }
    free((*play).musica);
}
