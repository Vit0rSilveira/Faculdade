#ifndef DATA_H
#define DATA_H

#include "stack.h"

// This file isn't TAD. It just has the functions used in the main.


/**
 * @brief Consumes the '\r' or '\n' and verify if it's EOF.
 * 
 * @return int 
 */
int is_end();

/**
 * @brief Verify if the element at the top is opposite the element received 
 * 
 * @param top 
 * @param c 
 * @return int 1 for the true or 0 for the false
 */
int is_opposite(char top, char c);

/**
 * @brief The quotation marks is a special case and this function does the
 * treatment the case.
 * 
 * @param c 
 * @return int 
 */
int is_specialCase(char c);

/**
 * @brief verify if the element is the input
 * 
 * @param c 
 * @return int int 1 for the true or 0 for the false
 */
int is_input(char c);

/**
 * @brief verify if the element is the output.
 * 
 * @param c 
 * @return int int 1 for the true or 0 for the false
 */
int is_output(char c);

/**
 * @brief verify if end of line.
 * 
 * @param c 
 * @return int int 1 for the true or 0 for the false
 */
int is_endLine(char c);

#endif