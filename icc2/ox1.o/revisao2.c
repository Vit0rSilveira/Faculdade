/**
 * Name: Vitor da Silveira Paula
 * 
 * Number: 10689651 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    int x;
    int y;
    int nLine;
    int nColumn;
    char *name;
    char **maze;
    bool exited;
} maze_t;

typedef struct {
    int way;
    int visited;
    int people;
    float explored;
} info_t;

char *recieve_name();
void alloc_memory(maze_t *maze);
void recieve_maze(maze_t *maze);
void print_maze(maze_t *maze);
void free_memory(maze_t *maze);
void print_info(info_t *info);
int count_data(maze_t *maze, char info);
void fill_maze(maze_t *maze, int coodX, int coodY);


int main() {
    maze_t maze;
    maze.exited = false;
    maze.name = recieve_name();

    recieve_maze(&maze);

    info_t info;
    info.way = count_data (&maze, '.');

    fill_maze(&maze, maze.x, maze.y);
    
    info.visited = count_data(&maze, '*');
    info.people = count_data(&maze, '#');
    info.explored = (info.visited * 100) / (info.way);

    print_maze(&maze);
    print_info(&info);

    free_memory(&maze);

    return 0;
}

/**
 * @brief This function recieve the name of archive for able to open it.
 * 
 * @return char* It's necessary free the memory after used.
 */
char *recieve_name() {
    char *name = NULL;
    char caractere = '\0';
    int cout = 0;

    while ((caractere = getchar()) == '\n');
    if (caractere != EOF)
        ungetc(caractere, stdin);
    
    do {
        caractere = getchar();

        name = realloc(name, ++cout * sizeof(char));
        name[cout - 1] = caractere;

    } while (caractere != '\n' && caractere != EOF);
    name[cout - 1] = '\0';

    return name;
}

void alloc_memory(maze_t *maze) {
    maze->maze = malloc(maze->nLine * sizeof(char *));

    for (int i = 0; i < maze->nLine; i++)
        maze->maze[i] = malloc(maze->nColumn * sizeof(char));

}

void recieve_maze(maze_t *maze) {
    FILE *archive = NULL;
    archive = fopen(maze->name, "r");

    if(archive == NULL) {
        printf("ERROR\n");
        return;
    }

    fscanf(archive, "%d", &maze->nLine);
    fscanf(archive, "%d", &maze->nColumn);
    fscanf(archive, "%d", &maze->x);
    fscanf(archive, "%d", &maze->y);

    char caractere = '\0';
    do {
        fscanf(archive, "%c", &caractere);
    } while(caractere == '\n');
    ungetc(caractere, archive);
    
    alloc_memory(maze);

    int returnRead = 0;
    int i = 0, j = 0;

    do {

        while((returnRead = fscanf(archive, "%c", &caractere)) != EOF
                && caractere != '\n') {
            maze->maze[i][j++] = caractere;
        }
        i++;
        j = 0;

    } while (returnRead != EOF);

    fclose(archive);
}

void fill_maze(maze_t *maze, int coodX, int coodY) {
    if (coodX >= maze->nLine|| coodX < 0 || coodY >= maze->nColumn || coodY < 0) {
        maze->exited = true;
        return;
    }
    if (maze->maze[coodX][coodY] != '.' || maze->exited) {
        return;
    }
    maze->maze[coodX][coodY] = '*';
    
    fill_maze(maze, coodX - 1, coodY);
    fill_maze(maze, coodX, coodY + 1);
    fill_maze(maze, coodX + 1, coodY);
    fill_maze(maze, coodX, coodY - 1);
}

void print_info(info_t *info) {
    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", info->people);
    printf("----Numero total de caminhos validos:   %d\n", info->way);
    printf("----Numero total de caminhos visitados: %d\n", info->visited);
    printf("----Exploracao total do labirinto: %.1lf%%\n", info->explored); 
}

void print_maze(maze_t *maze) {
    for(int i = 0; i < maze->nLine; i++) {
        for(int j = 0; j < maze->nColumn; j++) {
            printf("%c", maze->maze[i][j]);
        }
        printf("\n");
    }
}

void free_memory(maze_t *maze) {
    for (int i = 0; i < maze->nLine; i++)
        free(maze->maze[i]);
    free(maze->maze);

    free(maze->name);
}

int count_data(maze_t *maze, char info) {
    int cout = 0;
    for (int i = 0; i < maze->nLine; i++) {
        for (int j = 0; j < maze->nColumn; j++) {
            if(maze->maze[i][j] == info) 
                cout++;
        }
    }
    return cout;
}