#include "main.h"

int main(int argc, char const *argv[])
{
    char input_buffer[200];

    int precision;
    printf("Input wanted number of bits of precision [%ld - %ld] :", MPFR_PREC_MIN, MPFR_PREC_MAX/8);
    scanf("%d", &precision);
    mpfr_set_default_prec(precision);

    printf("Input expression : ");
    scanf("%s", input_buffer);

    token_list* list = read_tokens(input_buffer);
    syntax_tree* tree = read_expression(list);
    printf("Tree of input expression : \n");
    print_syntax_tree(tree);
    putchar('\n');

    printf("Optimised tree of input expression: \n");
    optimise_tree(&tree);
    print_syntax_tree(tree);
    putchar('\n');

    printf("Input all variables. Input \"!end\" to end input \n");
    char** name_array = init_name_array();
    range range_array[100];

    while (1)
    {
        scanf("%s", input_buffer);
        if(!strcmp(input_buffer, "!end"))
            break;
        read_variable(input_buffer, name_array, range_array);
    }
    printf("Evaluation of tree : ");
    print_range(evaluate_tree(&tree, name_array, range_array));
    putchar('\n');

    for (int i = 0; i < 100; i++)
    {
        if(name_array[i])
            free(name_array[i]);
        else
            break;
    }
    free(name_array);
    free_tree(tree);
    free_token_list(list, true);

    mpfr_free_cache();
    return 0;
}
