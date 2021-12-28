#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "stack.h"

int is_end() {
    char c;

    while(is_endLine(c = getchar()));

    if(c != EOF) {
        ungetc(c, stdin);
        return 0;
    }

    return 1;
}

int is_endLine(char c) {
    if(c == '\r' || c == '\n')
        return 1;

    return 0;
}

int is_input(char c) {
    if(c == '(' || c == '{' || c == '[')
        return 1;
    
    return 0;
}

int is_output(char c) {
    if (c == ')' || c == '}' || c == ']')
        return 1;
    
    return 0;
}

int is_specialCase(char c) {
    if(c == '"')
        return 1;

    return 0;
}

int is_opposite(char top, char c) {
    if(top == '(' && c == ')')
        return 1;
    else if(top == '{' && c == '}')
        return 1;
    else if(top == '[' && c == ']')
        return 1;
    
    return 0;
}