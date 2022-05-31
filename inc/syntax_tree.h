/**
 * @file syntax_tree.h
 * @author Grégory BRIVADY
 * @brief Simple definition of syntax trees
 * 
 */
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

/**
 * @brief Reads a tree from a list of token representing an expression
 * 
 * @param t_list 
 * @return syntax_tree* 
 */
syntax_tree* read_expression(token_list* t_list);

/**
 * @brief Prints a syntax tree
 * 
 * @param tree 
 */
void print_syntax_tree(syntax_tree* tree);

/**
 * @brief Free the tree and all its node, but NOT the content of the nodes
 * 
 * @param tree 
 */
void free_tree(syntax_tree* tree);

/**
 * @brief Create a simple node with no leaves from a single token
 * 
 * @param p_token 
 * @return syntax_tree* 
 */
syntax_tree* leaf_of_token(token* p_token);

#endif