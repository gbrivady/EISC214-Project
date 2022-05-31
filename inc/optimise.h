#ifndef OPTIMISE_H
#define OPTIMISE_H

#include <mpfr.h>

#include "syntax_tree.h"

void optimise_tree(syntax_tree** p_tree);

void simplify_constants(syntax_tree** p_tree);

void squash_l(syntax_tree** p_tree);
void squash_r(syntax_tree** p_tree);

void neutral_elements(syntax_tree** tree);

void negate_tree(syntax_tree* tree);

#endif