#ifndef PARSER_TOKEN_H
#define PARSER_TOKEN_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum token_type {BRACKET, OPERATION, VARIABLE, NUMBER} token_type;

typedef struct token
{
    token_type t_type;
    void* data;
} token;

typedef enum ope_data{ADD, SUB, MUL} ope_data;

typedef struct var_data{
    char* name;
    unsigned int size_name;
} var_data;

typedef struct num_data{
    int value;
} num_data;

int size_of_data(token_type t_type);

token* empty_token(token_type t_type, void* p_data);

void free_token(token* p_token);

void print_token(token* p_token);

void print_token_bracket(token* p_token);
void print_token_operation(token* p_token);
void print_token_variable(token* p_token);
void print_token_number(token* p_token);

#endif