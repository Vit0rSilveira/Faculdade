#ifndef ABB_H
#define ABB_H

typedef struct node node_t;
typedef struct tree tree_t;

struct tree {
    node_t *root;
};

/**
 * @brief Creat the tree
 * 
 * @return tree_t* 
 */
tree_t *creat();

/**
 * @brief free the memory allocate
 * 
 */
void finish_node_tree(node_t *root);

/**
 * @brief verify is the tree is empty
 * 
 * @param t 
 * @return int 
 */
int is_empty(tree_t *t);

/**
 * @brief printf the all node of the tree
 * 
 * @param root 
 * @return int 
 */
void print_tree(node_t *root);

/**
 * @brief Return the tree height 
 * 
 * @param root 
 * @return int 
 */
int height(node_t *root);

/**
 * @brief Print the tree in order
 * 
 * @param root 
 */
int in_order(node_t *root);

/**
 * @brief Print the tree in pre order
 * 
 * @param root 
 */
int pre_order(node_t *root);

/**
 * @brief print the tree in pos order
 * 
 * @param root 
 */
int pos_order(node_t *root);

/**
 * @brief search one value in tree
 * 
 * @param root 
 * @param value 
 * @return node_t* 
 */
node_t *search_value(node_t *root, int value);

/**
 * @brief push new node in the tree according to the abb rules
 * 
 * @param root 
 * @param value 
 * @return int 
 */
int push_node(node_t **root, int value);

/**
 * @brief remove the node
 * 
 * @param root 
 * @param value 
 * @return int 
 */
int remove_node(node_t **root, int value);



#endif