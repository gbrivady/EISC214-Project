
#include <stdio.h>
#include "input.h"
#include "token.h"
#include "syntax_tree.h"
#include "optimise.h"
#include "evaluate.h"

void test_str2tok(){

    printf("Begin testing \"token_from_string\" .... \n");
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

    printf("    - Done \n");
}

void test_token_list(){
    
    printf("Begin testing \"read_tokens\" .... \n");
    char* str = "   3*y+5*(variable - 37) + 74*a * e3  ";
    token_list* t_list = read_tokens(str);
    printf("    String successfully read : \n");
    print_token_list(t_list);
    putchar('\n');
    read_expression(t_list);
    putchar('\n');
    free_token_list(t_list, true);
    printf("    - Done \n");

}

int main(int argc, char const *argv[])
{
    //test_str2tok();
    //test_token_list();
    // print_syntax_tree(read_expression(read_tokens("1+2-3+4-5"))); //OK
    // putchar('\n');
    // print_syntax_tree(read_expression(read_tokens("1*2+3*4-7")));
    // putchar('\n');
    // print_syntax_tree(read_expression(read_tokens("2+1-3*8+9")));
    // putchar('\n');
    // token_list* list = read_tokens("dzae + (1-3) * 8 + 9 ");
    token_list* list = read_tokens("0 + (1-3) * 1 + 9.5 * zz");
    syntax_tree* tree = read_expression(list);
    print_syntax_tree(tree);
    putchar('\n');

    optimise_tree(&tree);
    print_syntax_tree(tree);
    // negate_tree(tree);
    // print_syntax_tree(tree);
    // putchar('\n');

    // neutral_elements(&(tree->left_node));
    // neutral_elements(&(tree->left_node));
    // print_syntax_tree(tree);
    putchar('\n');

    char** name_array = init_name_array();
    range range_array[100];
    print_range(evaluate_tree(&tree, name_array, range_array));
    putchar('\n');
    free_tree(tree);
    free_token_list(list, true);

    // list = read_tokens("(1-3) + bb ");
    // tree = read_expression(list);
    // print_syntax_tree(tree);
    // putchar('\n');
    // simplify_constants(&(tree->left_node));
    // print_syntax_tree(tree);
    // putchar('\n');
    // free_tree(tree);
    // free_token_list(list, true);

    // range a = {1, 3};
    // range b = {10, 11};
    // print_range(negate_range(a));
    // putchar('\n');

    // print_range(range_of_string("[4.2132122;3213.321]"));
    // putchar('\n');

    // char** name_array = init_name_array();
    // range range_array[100];
    // read_variable("zz=[46;55]", name_array, range_array);
    // printf("%s=", name_array[0]);
    // print_range(range_array[0]);
    // putchar('\n');    
    
    // read_variable("zzuu=[49;55]", name_array, range_array);
    // printf("%s=", name_array[1]);
    // print_range(range_array[1]);
    // putchar('\n');

    // print_range(find_value("zz", name_array, range_array));    
    // putchar('\n');
    // print_range(find_value("zzuu", name_array, range_array));
    // putchar('\n');
    // print_range(find_value("zz", name_array, range_array));
    // putchar('\n');    
    // print_range(find_value("zaz", name_array, range_array));
    // putchar('\n');
    for (int i = 0; i < 100; i++)
    {
        if(name_array[i])
            free(name_array[i]);
        else
            break;
    }
    free(name_array);
    
    return 0;
}
