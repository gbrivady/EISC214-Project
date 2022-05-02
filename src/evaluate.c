#include "evaluate.h"

char** init_name_array(){
    char** name_array = malloc(sizeof(char*)*100);
    for (int i = 0; i < 100; i++)
    {
        name_array[i] = NULL;
    }
    return name_array;
}

void read_variable(char* str, char** name_array, range* range_array){
    int i;
    for (i = 0; i < 100; i++)
    {
        if (name_array[i] == NULL)
        {
            break;
        }
        
    }
    int j;
    for (j = 0; j < strlen(str); j++)
    {
        if(str[j] == '=')
            break;
    }
    char* var_name = malloc(sizeof(char)*(j+1));
    strncpy(var_name, str, j);
    var_name[j] = '\0';
    name_array[i] = var_name;
    range_array[i] = range_of_string(str+j+1);
}

range find_value(char* name, char** name_array, range* range_array){
    int i;
    for (i = 0; i < 100; i++){
        if(name_array[i] == NULL){
            char str[100];
            printf("Variable %s not found. Enter value range :\n \t");
            scanf("%s", str);
            read_variable(str, name_array, range_array);
            break;
        }
        if(!strcmp(name_array[i], name))
            break;
    }
    return range_array[i];
}

range evaluate_tree(syntax_tree** p_tree, char** name_array, range* range_array){
    range value_l;
    range value_r;
    token* p_token = (*p_tree)->root;
    if (p_token->t_type == NUMBER){
        return ((num_data*)p_token->data)->value;
    }
    if (p_token->t_type == VARIABLE){
        //replaces the variable by its value
        value_l = find_value(((var_data*)p_token->data)->name, name_array, range_array);
        if(((var_data*)p_token->data)->is_negative)
            value_l = negate_range(value_l);
        return value_l;
    }
    if ((*p_tree)->left_node)
    {
        value_l = evaluate_tree(&(*p_tree)->left_node, name_array, range_array);
    }
    if((*p_tree)->right_node){
        value_r = evaluate_tree(&(*p_tree)->right_node, name_array, range_array);
    }
    ope_data* operation = (ope_data*) (*p_tree)->root->data;
    switch (*operation)
    {
    case ADD:
        return add_range(value_l, value_r);
    case SUB:
        return sub_range(value_l, value_r);
    case MUL:
        return mul_range(value_l, value_r);
    case DIV:
        return div_range(value_l, value_r);
    default:
        exit(1);
    }

    // We remove the operation node, and one number
    // Then we move the second number and replace its value ( for memory management )
}
