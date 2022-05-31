/**
 * @file token.h
 * @author Grégory BRIVADY
 * @brief Definition of computer-readable tokens
 * 
 */
#ifndef PARSER_TOKEN_H
#define PARSER_TOKEN_H

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "num_data.h"

typedef enum token_type {OPERATION = -1, BRACKET = 0, VARIABLE, NUMBER} token_type;

typedef struct token
{
    token_type t_type;
    void* data;
} token;

typedef enum ope_data{ADD, SUB, MUL, DIV} ope_data;

typedef struct var_data{
    char* name;
    unsigned int size_name;
    bool is_negative;
} var_data;

int size_of_data(token_type t_type);

/**
 * @brief Allocates memory for an empty token
 * 
 * @param t_type 
 * @return token* 
 */
token* empty_token(token_type t_type);


void free_token(token* p_token);

void print_token(token* p_token);

void print_token_bracket(token* p_token);
void print_token_operation(token* p_token);
void print_token_variable(token* p_token);
void print_token_number(token* p_token);

/**
 * @brief Doubly-linked token lists, to allow popping of elements in constant time
 * when travelling through the list
 * 
 */
typedef struct token_list_cell
{
    token* data;
    struct token_list_cell* prev;
    struct token_list_cell* next;

} token_list_cell;

typedef struct token_list
{
    token_list_cell* first;
    token_list_cell* last; //to append elements in O(1) time
} token_list;

void append_token(token_list* p_list, token* p_token);

void print_token_list(token_list* p_t_list);

void free_token_list(token_list* p_t_list, bool free_content);


#endif