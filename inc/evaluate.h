/**
 * @file evaluate.h
 * @author Grégory BRIVADY
 * @brief Everything required to compute the value of a syntax_tre
 * 
 */

#ifndef EVALUATE_H
#define EVALUATE_H

#include "syntax_tree.h"

/**
 * @brief Creates an empty array of string to store variable names
 * 
 * @return char** 
 */
char** init_name_array();

/**
 * @brief Read a variable from a string, and puts its name and value inside two arrays, such that 
 * the element of the value array at index i, is the value of the variable whose name is at index i of 
 * the name array.
 * 
 * @param str Input string
 * @param name_array Array of names
 * @param range_array Array of values
 */
void read_variable(char* str, char** name_array, range* range_array);

/**
 * @brief Find a value corresponding to a certain name.
 * 
 * @param name Input name
 * @param name_array Array of names
 * @param range_array Array of values
 * @return Value at index i of range_array, with index i being the first index 
 * such that name_array[i]==name
 */
range find_value(char* name, char** name_array, range* range_array);

/**
 * @brief Evaluate a syntax tree.
 * 
 * @param p_tree Pointer to a syntax tree pointer.
 * @param name_array Array of variable names
 * @param range_array Array of variable values
 * @return Computed expression 
 */
range evaluate_tree(syntax_tree** p_tree, char** name_array, range* range_array);

#endif 
