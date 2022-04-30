#include "main.h"
#include "input.h"
#include "token.h"
int main(int argc, char const *argv[])
{
    token* p_token = token_from_string("(");
    print_token(p_token);
    printf("\n");
    free_token(p_token);

    p_token = token_from_string("(");
    print_token(p_token);
    printf("\n");
    free_token(p_token);

    p_token = token_from_string("(");
    print_token(p_token);
    printf("\n");
    free_token(p_token);
    

    p_token = token_from_string("(");
    print_token(p_token);
    printf("\n");
    free_token(p_token);

    p_token = token_from_string("(");
    print_token(p_token);
    printf("\n");
    free_token(p_token);
    return 0;
}
