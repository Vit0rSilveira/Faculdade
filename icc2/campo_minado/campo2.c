/**
 * Student: Vitor da Silveira Paula - 10689651
 * SCC0201 - Introdução à Ciência da Computação 2
 * Exercise: Campo Minado
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

enum commands {
    PRINT = 1,
    PRINT_TIP,
    CONTROL
};

#define BOMB '*'

typedef struct {
    int lineSize;
    int columnSize;
    char **board;
    char **boardTip;
    char *name;
} minefield_t;


char *read_line(FILE *file, minefield_t *minefield);
char **recieve_minefield(minefield_t *minefield);
void print_minefield(minefield_t *minefield, bool tip);
int count_tip(int i, int j, minefield_t *minefield);
void alloc_tip(minefield_t *minefield);
void minefield_tip(minefield_t *minefield);
void atribuete_x(minefield_t *minefield);
void user_control(minefield_t *minefield);
void space_white(int line, int column, minefield_t *minefield);
void free_memory(minefield_t *minefield);


int main(int argc, char *argv[]) {
    int command;
    scanf("%d", &command);

    minefield_t minefield;
    minefield.board = recieve_minefield(&minefield);
    minefield_tip(&minefield);

    switch (command) {
    case PRINT:
        print_minefield(&minefield, false);
        break;
    case PRINT_TIP:
        print_minefield(&minefield, true);
        break;
    case CONTROL:
        user_control(&minefield);
        break;
    }

    free_memory(&minefield);

    return 0;
}

/**
 * @brief This function, reads one line of the stdin or the archive.
 * 
 * @param file input of reading, it's the stdin or archive with board.
 * @param isName checks if it's necessary to put of terminator of 
 * string or no.
 * @param minefield struct with of datas
 * @return char* line read. It's necessary release the memory after use.
 */
char *read_line(FILE *file, minefield_t *minefield) {
    char *line = NULL;
    char caracterer = '\0';

    while ((caracterer = fgetc(file)) == '\n');
    if (caracterer != EOF)
        ungetc(caracterer, file);

    minefield->columnSize = 0;

    while ((caracterer = fgetc(file)) != '\n') {
        line = realloc(line, ++(minefield->columnSize) * sizeof(char));
        line[minefield->columnSize - 1] = caracterer;
    }
    line = realloc(line, (minefield->columnSize + 1) * sizeof(char));
    line[minefield->columnSize] = '\0';

    return line;
}

/**
 * @brief This function recieve the minefield. For this, it recieves the 
 * filename and open the archive for read. In while, it was necessary verify 
 * the last line, because, this line doesn't have usable information,
 * only end of file.
 * 
 * @return char** minefield, and it's necessary release the memory alocated
 */
char **recieve_minefield(minefield_t *minefield) {
    minefield->name = read_line(stdin, minefield);

    FILE *archive = fopen(minefield->name, "r");
    if (archive == NULL) {
        printf("failure to open the archive\n");
        free(minefield->name);

        return NULL;
    }

    char **board = NULL;

    minefield->lineSize = 0;
    while (true) {
        char c;
        if ((c = fgetc(archive)) == EOF)
            break;
        ungetc(c, archive);

        board = realloc(board, ++(minefield->lineSize) * sizeof(char *));
        board[minefield->lineSize - 1] = read_line(archive, minefield);
    }
    fclose(archive);

    return board;
}

void print_minefield(minefield_t *minefield, bool tip) {
    for (int i = 0; i < minefield->lineSize; i++) {
        if (tip == false)
            printf("%s", minefield->board[i]);
        else
            printf("%s", minefield->boardTip[i]);
        printf("\n");
    }
}

int count_tip(int i, int j, minefield_t *minefield) {
    int count = 0;
    int lMax = minefield->lineSize;
    int cMax = minefield->columnSize;

    if(i - 1>= 0 && j - 1 >= 0 && minefield->board[i - 1][j - 1] == BOMB)
        count++;
    if(i - 1 >= 0 && minefield->board[i - 1][j] == BOMB)
        count++;
    if(i - 1>= 0 && j + 1 < cMax && minefield->board[i - 1][j + 1] == BOMB)
        count++;
    if(j - 1 >= 0  && minefield->board[i][j - 1] == BOMB)
        count++;
    if(j + 1 < cMax && minefield->board[i][j + 1] == BOMB)
        count++;
    if(i + 1 < lMax && j - 1 >= 0 && minefield->board[i + 1][j - 1] == BOMB)
        count++;
    if(i + 1 < lMax && minefield->board[i + 1][j] == BOMB)
        count++;
    if(i + 1 < lMax && j + 1 < cMax && minefield->board[i + 1][j + 1] == BOMB)
        count++;

    return count;
}

void alloc_tip(minefield_t *minefield) {
    minefield->boardTip = malloc(minefield->lineSize * sizeof(char *));

    for (int i = 0; i < minefield->lineSize; i++)
        minefield->boardTip[i] = malloc((minefield->columnSize + 1) * sizeof(char));

    for (int i = 0; i < minefield->lineSize; i++){
        for (int j = 0; j <= minefield->columnSize; j++)
            minefield->boardTip[i][j] = '\0';
    }
}

/**
 * @brief This function, allocate the memory of the board with tips, and fill 
 * it.
 * 
 * @param minefield Struct with all the important datas of the execution.
 */
void minefield_tip(minefield_t *minefield) {
    alloc_tip(minefield);

    for (int i = 0; i < minefield->lineSize; i++) {
        for (int j = 0; j < minefield->columnSize; j++) {
            int count = 0;
            if (minefield->board[i][j] != BOMB)
                count = count_tip(i, j, minefield);
            else
                count = 0;

            if (count != 0)
                minefield->boardTip[i][j] = count + '0';
            else
                minefield->boardTip[i][j] = minefield->board[i][j];
        }
    }
}

/**
 * @brief This function, does the minefield mapping until find one tip.
 * 
 * @param line in the line point coordinate
 * @param column in the column point coordinate
 * @param minefield struct with data importants.
 */
void space_white(int line, int column, minefield_t *minefield) {
    if(line < 0 || column < 0)
        return;
    if(line >= minefield->lineSize|| column >= minefield->columnSize)
        return;
    if (minefield->board[line][column] != 'X')
        return;
    if (isdigit(minefield->boardTip[line][column]))
        minefield->board[line][column] = minefield->boardTip[line][column];

    if(minefield->boardTip[line][column] == '.') {
        minefield->board[line][column] = minefield->boardTip[line][column];

        space_white(line - 1, column - 1, minefield);
        space_white(line - 1, column, minefield);
        space_white(line - 1, column + 1, minefield);
        space_white(line, column - 1, minefield);
        space_white(line, column + 1, minefield);
        space_white(line + 1, column - 1, minefield);
        space_white(line + 1, column, minefield);
        space_white(line + 1, column + 1, minefield);
    }
}

void atribuete_x(minefield_t *minefield) {
    for (int i = 0; i < minefield->lineSize; i++) {
            for (int j = 0; j < minefield->columnSize; j++)
                minefield->board[i][j] = 'X';
        }
}

/**
 * @brief User control, recieve the user points and according whats it's do th
 * 
 * @param minefield 
 */
void user_control(minefield_t *minefield) {
    int line, column;
    scanf(" %d %d", &line, &column);

    if (minefield->board[line][column] == BOMB)
        print_minefield(minefield, true);

    else if (isdigit(minefield->boardTip[line][column])) {

        for (int i = 0; i < minefield->lineSize; i++) {
            for (int j = 0; j < minefield->columnSize; j++) {
                if (line == i && column == j)
                    printf("%c", minefield->boardTip[i][j]);
                else
                    printf("X");
            }
            printf("\n");
        }
    }
    else {
        atribuete_x(minefield);
        space_white(line, column, minefield);
        print_minefield(minefield, false);
    }
}

void free_memory(minefield_t *minefield) {
    free(minefield->name);

    for (int i = 0; i < minefield->lineSize; i++) {
        free(minefield->board[i]);
        free(minefield->boardTip[i]);
    }
    free(minefield->board);
    free(minefield->boardTip);
}