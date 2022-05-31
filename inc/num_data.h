#ifndef NUM_DATA_H
#define NUM_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpfr.h>

struct range
{
    mpfr_t x;
    mpfr_t y;
} typedef range;

struct num_data
{
    range value;
} typedef num_data;

range add_range(range a, range b);

range sub_range(range a, range b);

range mul_range(range a, range b);

range negate_range(range a);

range inv_range(range a);

range div_range(range a, range b);

void print_range(range a);

range range_of_string(char* str);

#endif