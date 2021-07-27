/*---------------------------------------------------------------------- 
                       Universidade de São Paulo
       Instituto de Ciências Matemáticas e de Computação - ICMC
                Departamento de Ciências de Computação - SCC
                SCC0221 - Introdução a Ciência de Computação 1
                   Nome: Vitor da Silveira Paula - 10689651           
---------------------------------------------------------------------- */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


typedef struct Matriz {
    int qtdLinhas;
    int qtdColunas;
    char **dados;
} matriz_t;

typedef struct Troca {
    char caracterer;
    int x;
    int y;
} troca_t;


char *receberNome();
char **receberDesenho(char *nomeArquivo, matriz_t *arte);
void mostrarDesenho(matriz_t arte);
void desalocarMemoria(char *nomeArquivo, matriz_t arte);
void preencherArte(char caractereTroca, troca_t troca, matriz_t *arte);
void salvarArquivo(char *nomeArquivo, matriz_t arte);
void enquadraArte(char *nome_do_arquivo_da_arte,
int altura_do_quadro,
int largura_do_quadro
);


int main() {
    char *nomeArquivo = receberNome();

    int qtdPreenchimeno;
    scanf("%d", &qtdPreenchimeno);

    matriz_t arte = {0 , 0, receberDesenho(nomeArquivo, &arte)};

    printf("Arte inicial:\n");
    mostrarDesenho(arte);
    
    troca_t troca;
    for (int i = 0; i < qtdPreenchimeno; i++) {
        scanf(" %c %d %d", &troca.caracterer, &troca.x, &troca.y);
        preencherArte(arte.dados[troca.x][troca.y], troca, &arte);

        printf("\nArte apos a etapa %d:\n", i);
        mostrarDesenho(arte);
    }

    salvarArquivo(nomeArquivo, arte);

    printf("\nArte enquadrada:\n");
    enquadraArte(nomeArquivo, arte.qtdLinhas, arte.qtdColunas);

    desalocarMemoria(nomeArquivo, arte);
    
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

        nome[tamanhoNome - 1] = caractereNome;

        if (caractereNome == '\n' || caractereNome == '\r') {
            nome[tamanhoNome - 1] = '\0';
            break;
        }
    }    
    return nome;
}

/**
 * @brief Recebe a matriz que contem o desenho.
 * 
 * @param nomeArquivo Nome do Arquivo do desenho.
 * @param arte Matriz que armazenará o desenho.
 * @return char** É necessário desalocar esta memória depois.
 */
char **receberDesenho (char *nomeArquivo, matriz_t *arte) {
    FILE *arquivo = NULL;
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Arquivo Não existe\n");
        return NULL;
    }

    char **desenho = NULL;
    char caractere = '\0';
    int retornoLeitura;

    do {
        desenho = realloc(desenho, ++(arte->qtdLinhas) * sizeof(char *));
        arte->qtdColunas = 0;
        desenho[arte->qtdLinhas - 1] = NULL;
        
        do {
            retornoLeitura = fscanf(arquivo, "%c", &caractere);

            desenho[arte->qtdLinhas - 1] = realloc(
                desenho[arte->qtdLinhas - 1], 
                ++(arte->qtdColunas) * sizeof(char)
            );

            desenho[arte->qtdLinhas  - 1][arte->qtdColunas - 1] = caractere;

        } while (caractere != '\n' && retornoLeitura != EOF);

        desenho[arte->qtdLinhas  - 1] = realloc(
            desenho[arte->qtdLinhas - 1], 
            --(arte->qtdColunas) * sizeof(char)
        );

    } while (retornoLeitura != EOF);
    fclose(arquivo);

    return desenho;
}

void mostrarDesenho(matriz_t arte) {
    for (int i = 0; i < arte.qtdLinhas; i++) {
        for (int j = 0; j < arte.qtdColunas; j++) {   
            printf("%c", arte.dados[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Função recursiva que faz o preenchimento da arte.
 *
 * @param caracterePrincipal Caractere para verificar se terá a troca ou não.
 * @param troca Struct com os dados para a troca.
 * @param arte Ponteiro para a struct que possue o desenho a ser preenchido.
 */
void preencherArte(char caracterePrincipal, troca_t troca, matriz_t *arte) {
    int x = troca.x;
    int y = troca.y;

    if (x >= 0 && y >= 0 && x < arte->qtdLinhas && y < arte->qtdColunas) {
        if (arte->dados[x][y] == caracterePrincipal) {
            arte->dados[x][y] = troca.caracterer;

            troca.x = x;
            troca.y = y - 1;
            preencherArte(caracterePrincipal, troca, arte);

            troca.x = x;
            troca.y = y + 1;
            preencherArte(caracterePrincipal, troca, arte);

            troca.y = y;
            troca.x = x - 1;
            preencherArte(caracterePrincipal, troca, arte);

            troca.y = y;
            troca.x = x + 1;
            preencherArte(caracterePrincipal, troca, arte);
        }
    }
    return;
}

void salvarArquivo(char *nomeArquivo, matriz_t arte) {
    FILE *arquivo = NULL;
    arquivo = fopen(nomeArquivo, "w");
    for (int i = 0; i < arte.qtdLinhas; i++) {
        for (int j = 0; j < arte.qtdColunas; j++) {
            fprintf(arquivo, "%c", arte.dados[i][j]);
        }
        if (i < (arte.qtdLinhas - 1))
            fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}

void enquadraArte(
	char *nome_do_arquivo_da_arte,
	int  altura_do_quadro,
	int  largura_do_quadro
) {
	FILE *f_arte_ptr = fopen(nome_do_arquivo_da_arte, "r");
	if (f_arte_ptr == NULL) {
		printf(
			"Erro na abertura do arquivo, "
			"Você esqueceu de fechar o arquivo antes? "
			"Ou deu free na string com o nome sem querer?\n"
		);

		exit(EXIT_FAILURE);
	}

	int qtd_espc_comeco;
	const char *apoio;
	if (largura_do_quadro % 2 == 0) {
		qtd_espc_comeco = largura_do_quadro / 2;
		apoio           = "/\\";
	} else {
		qtd_espc_comeco = largura_do_quadro / 2 + 1;
		apoio           = "Ʌ";
	}

	for (int i = 0; i < qtd_espc_comeco; i++) printf(" ");
	printf("%s\n", apoio);

	printf("╭");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╮\n");

	for (int i = 0; i < altura_do_quadro; i++) {
		printf("|");
		for (int j = 0; j < largura_do_quadro; j++) {
			char pixel_atual = fgetc(f_arte_ptr);
			printf("%c", pixel_atual);
		}
		printf("|");

		char quebra = fgetc(f_arte_ptr);
		if (quebra != EOF) printf("%c", quebra);
	};
	fclose(f_arte_ptr);

	printf("\n╰");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╯\n");
}

void desalocarMemoria(char *nomeArquivo, matriz_t arte) {
    for (int i = 0; i < arte.qtdLinhas; i++) 
        free(arte.dados[i]);
    free(arte.dados);
    free(nomeArquivo);
}
