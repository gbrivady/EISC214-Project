#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "token.h"

typedef struct syntax_tree
{
    token* root;
    struct syntax_tree* left_node;
    struct syntax_tree* right_node;
    
} syntax_tree;

syntax_tree* read_expression(token_list* t_list);

void print_syntax_tree(syntax_tree* tree);
void free_tree(syntax_tree* tree);

#endif