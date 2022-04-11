#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

typedef struct token_list_cell
{
    token* data;
    struct token_list_cell* next;

} token_list_cell;

typedef struct token_list
{
    token_list_cell* first;
    token_list_cell* last;
} token_list;


token* token_from_string(char* str);

token_list* read_tokens(char* str);

void append_token(token_list* p_list, token* p_token);

void print_token_list(token_list* p_t_list);

void free_token_list(token_list* p_t_list);

#endif