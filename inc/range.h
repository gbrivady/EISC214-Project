#ifndef RANGE_H
#define RANGE_H

#include <stdio.h>

struct range
{
    double x;
    double y;
} typedef range;

range add_range(range a, range b);

range sub_range(range a, range b);

range mul_range(range a, range b);

range negate_range(range a);

range inv_range(range a);

range div_range(range a, range b);

void print_range(range a);

#endif