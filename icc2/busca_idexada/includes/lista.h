#ifndef LIST_H
#define LIST_H


typedef struct list list_t;
typedef struct node node_t;
typedef struct index index_t;


struct node {
    char   *word;
    node_t *next;
};

struct list {
    node_t *begin;
    node_t *end;
};

struct index {
    //It's used string, because with string can use string compare functions
    char   *firstChar;
    node_t *address;
};



/**
 * @brief Creat the list;
 * 
 * @return list_t* 
 */
list_t *create();

/**
 * @brief Deallocate the memory and 
 * 
 * @param l 
 */
void delete_list(list_t *l);

/**
 * @brief push the new node in the list
 * 
 */
void push_node_list(list_t *l, char *word);

/**
 * @brief print list elements based on ordered quantity
 * 
 * @param l 
 */
void print_list(list_t *l, int qtd);

/**
 * @brief update the index array according to the first word of each letter.
 * 
 * @param l 
 * @param array 
 */
void update_array_index(list_t *l, index_t *array);

/**
 * @brief Searches a word in the list, starting at a letter in the array. If a
 * word exists, returns the amount of nodes it went through.
 * 
 * 
 * @param l 
 * @param a 
 * @param word 
 * @return int 
 */
int search_list(list_t *l, index_t *a, char *word);


#endif