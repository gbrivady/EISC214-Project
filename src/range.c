#include <float.h>
#include "range.h"

range add_range(range a, range b){
    range c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

range sub_range(range a, range b){
    range c;
    c.x = a.x - b.y;
    c.y = a.y - b.x;
    return c;
}

range mul_range(range a, range b){
    double prod[4];
    prod[0] = a.x*b.x;
    prod[1] = a.y*b.y;
    prod[2] = a.x*b.y;
    prod[3] = a.y*b.x;
    range c;
    c.x = DBL_MAX;
    c.y = DBL_MIN;
    for (int i = 0; i < 4; i++)
    {
        if(prod[i] < c.x)
            c.x = prod[i];
        if(prod[i] > c.y)
            c.y = prod[i];
    }
    return c;
}

range negate_range(range a){
    a.x *= -1;
    a.y *= -1;
    double temp = a.x;
    a.x = a.y;
    a.y = temp;
    return a;
}

range inv_range(range a){
    range c;
    double inv1 = 1/a.x;
    double inv2 = 1/a.y;
    if(inv1 <= inv2){
        c.x = inv1;
        c.y = inv2;
        return c;
    }
    c.x = inv2;
    c.y = inv1;
    return c;
}

range div_range(range a, range b){
    range c = inv_range(b);
    c = mul_range(a, c);
    return c;
}

void print_range(range a){
    printf("[%lf; %lf]", a.x, a.y);
}

range range_of_string(char* str){
    if (str[0] != '[')
    {
        exit(1);
    }
    range a;
    a.x = strtod(str+1, &str);
    if (str[0] != ';'){
        exit(1);
    }
    a.y = strtod(str+1, &str);
    return a;
    
}