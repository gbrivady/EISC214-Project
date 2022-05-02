#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

token* token_from_string(char** p_str);

token_list* read_tokens(char* str);

#endif