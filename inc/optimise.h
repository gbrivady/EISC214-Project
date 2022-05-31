/**
 * @file optimise.h
 * @author Grégory BRIVADY
 * @brief Optimisation of syntax trees before evaluation
 * 
 */
#ifndef OPTIMISE_H
#define OPTIMISE_H

#include <mpfr.h>

#include "syntax_tree.h"

/**
 * @brief Does its best efforts to optimise a syntax tree
 * 
 * @param p_tree 
 */
void optimise_tree(syntax_tree** p_tree);

/**
 * @brief Simplify nodes where both leafs are constants, to a single constant node.
 * 
 * @param p_tree 
 */
void simplify_constants(syntax_tree** p_tree);

/**
 * @brief Deletes left leaf and put the right one as root
 * 
 * @param p_tree 
 */
void squash_l(syntax_tree** p_tree);

/**
 * @brief Deletes right leaf and put the left one as root
 * 
 * @param p_tree 
 */
void squash_r(syntax_tree** p_tree);

/**
 * @brief Simplify operations with neutral elements on one side of the operation
 * 
 * @param tree 
 */
void neutral_elements(syntax_tree** tree);

/**
 * @brief Negates all the elements of a tree
 * 
 * @param tree 
 */
void negate_tree(syntax_tree* tree);

#endif