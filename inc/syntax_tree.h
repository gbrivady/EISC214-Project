#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "token.h"

#define MAX_PRIORITY 2

typedef struct syntax_tree
{
    token* root;
    struct syntax_tree* left_node;
    struct syntax_tree* right_node;
    
} syntax_tree;

syntax_tree* read_expression(token_list* t_list);

void print_syntax_tree(syntax_tree* tree);
void free_tree(syntax_tree* tree);
syntax_tree* leaf_of_token(token* p_token);

#endif