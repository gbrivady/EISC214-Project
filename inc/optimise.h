#ifndef OPTIMISE_H
#define OPTIMISE_H

#include "syntax_tree.h"

void optimise_tree(syntax_tree** p_tree);

void simplify_constants(syntax_tree** p_tree);

void neutral_elements(syntax_tree** tree);

void negate_tree(syntax_tree* tree);

#endif