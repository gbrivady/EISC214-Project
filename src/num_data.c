#include "num_data.h"

range add_range(range a, range b){
    range c;
    mpfr_init(c.x);
    mpfr_init(c.y);
    mpfr_add(c.x, a.x, b.x, MPFR_RNDN);
    mpfr_add(c.y, a.y, b.y, MPFR_RNDN);
    return c;
}

range sub_range(range a, range b){
    range c;
    mpfr_init(c.x);
    mpfr_init(c.y);
    // c.x = a.x - b.y;
    // c.y = a.y - b.x;
    mpfr_sub(c.x, a.x, b.y, MPFR_RNDN);
    mpfr_sub(c.y, a.y, b.x, MPFR_RNDN);
    return c;
}

range mul_range(range a, range b){
    mpfr_t* prod = malloc(sizeof(mpfr_t)*4);
    mpfr_init(prod[0]);
    mpfr_init(prod[1]); 
    mpfr_init(prod[2]);
    mpfr_init(prod[3]);
    mpfr_mul(prod[0], a.x, b.x, MPFR_RNDN);
    mpfr_mul(prod[1], a.y, b.y, MPFR_RNDN);
    mpfr_mul(prod[2], a.x, b.y, MPFR_RNDN);
    mpfr_mul(prod[3], a.y, b.x, MPFR_RNDN);
    range c;
    mpfr_init(c.x);
    mpfr_init(c.y);;

    mpfr_min(c.x, prod[0], prod[1], MPFR_RNDN);
    mpfr_max(c.y, prod[0], prod[1], MPFR_RNDN);
    for (int i = 2; i < 4; i++)
    {
        mpfr_min(c.x, c.x, prod[i], MPFR_RNDN);
        mpfr_max(c.y, c.y, prod[i], MPFR_RNDN);
    }
    mpfr_clear(prod[0]);
    mpfr_clear(prod[1]);
    mpfr_clear(prod[2]);
    mpfr_clear(prod[3]);

    free(prod);
    return c;
}

range negate_range(range a){
    mpfr_neg(a.x, a.x, MPFR_RNDN);
    mpfr_neg(a.y, a.y, MPFR_RNDN);
    mpfr_swap(a.x, a.y);
    // double temp = a.x;
    // a.x = a.y;
    // a.y = temp;
    return a;
}

range inv_range(range a){
    range c;
    mpfr_init(c.x);
    mpfr_init(c.y);
    mpfr_pow_si(c.x, a.x, -1, MPFR_RNDN);
    mpfr_pow_si(c.y, a.y, -1, MPFR_RNDN);
    // double inv1 = 1/a.x;
    // double inv2 = 1/a.y;
    if(mpfr_lessequal_p(c.x, c.y)){
        return c;
    }
    mpfr_swap(c.x, c.y);
    return c;
}

range div_range(range a, range b){
    range c = inv_range(b);
    c = mul_range(a, c);
    return c;
}

void print_range(range a){
    mpfr_printf("[%Re; %Re]", a.x, a.y);
}

range range_of_string(char* str){
    if (str[0] != '[')
    {
        exit(1);
    }
    range a;
    mpfr_init(a.x);
    mpfr_init(a.y);
    mpfr_strtofr(a.x, str+1, &str, 10, MPFR_RNDN);
    // a.x = strtod(str+1, &str);
    if (str[0] != ';'){
        exit(1);
    }
    mpfr_strtofr(a.y, str+1, &str, 10, MPFR_RNDN);
    return a;
    
}