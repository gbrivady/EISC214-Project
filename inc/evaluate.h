#ifndef EVALUATE_H
#define EVALUATE_H

#include "syntax_tree.h"

char** init_name_array();

void read_variable(char* str, char** name_array, range* range_array);

range find_value(char* name, char** name_array, range* range_array);

range evaluate_tree(syntax_tree** p_tree, char** name_array, range* range_array);

#endif 
