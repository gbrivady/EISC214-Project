
#include <stdio.h>
#include "input.h"
#include "token.h"

void test_str2tok(){

    /*  TESTING SINGLE CHAR TOKENS */
    token* p_token = token_from_string("(");
    print_token(p_token);
    printf("\n");
    free_token(p_token);

    p_token = token_from_string(")");
    print_token(p_token);
    printf("\n");
    free_token(p_token);

    p_token = token_from_string("+");
    print_token(p_token);
    printf("\n");
    free_token(p_token);

    p_token = token_from_string("-");
    print_token(p_token);
    printf("\n");
    free_token(p_token);

    p_token = token_from_string("*");
    print_token(p_token);
    printf("\n");
    free_token(p_token);

    /*  TESTING VARIABLES TOKENS */

    p_token = token_from_string("abcd");
    print_token(p_token);
    printf("\n");
    free_token(p_token);

    p_token = token_from_string("abcd213z");
    print_token(p_token);
    printf("\n");
    free_token(p_token);
    
    p_token = token_from_string("abc23e * 37 + 2");
    print_token(p_token);
    printf("\n");
    free_token(p_token);    
    
    /*  TESTING INTEGERS TOKENS */

    p_token = token_from_string("1234");
    print_token(p_token);
    printf("\n");
    free_token(p_token);

    p_token = token_from_string("123456*2132");
    print_token(p_token);
    printf("\n");
    free_token(p_token);

    p_token = token_from_string("22abb");
    print_token(p_token);
    printf("\n");
    free_token(p_token);
}

int main(int argc, char const *argv[])
{
    test_str2tok();
    return 0;
}
