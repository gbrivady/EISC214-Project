/**
 * @file input.h
 * @author Grégort BRIVADY
 * @brief Reading human-readable strings as input to create a list of computer-readable tokens
 * 
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

/**
 * @brief Read a single token from the pointer to a string. If the read token is a number,
 * moves the pointer to the end of this number.
 * 
 * @param p_str Input pointer to the string
 * @return Read token
 */
token* token_from_string(char** p_str);

/**
 * @brief Reads a list of tokens from a string
 * 
 * @param str Input string
 * @return A list of computer-readable tokens
 */
token_list* read_tokens(char* str);

#endif