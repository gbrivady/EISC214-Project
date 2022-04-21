#include "syntax_tree.h"

syntax_tree* leaf_of_token(token* p_token){
    if (p_token->t_type == BRACKET){
        return read_expression(*((token_list**)p_token->data));
    }

    syntax_tree* leaf = malloc(sizeof(syntax_tree));
    leaf->left_node = NULL;
    leaf->right_node = NULL;
    leaf->root = p_token;
    return leaf;
}

syntax_tree* eat_token(token_list_cell** p_cell){
    syntax_tree* node = leaf_of_token((*p_cell)->data);
    *p_cell = (*p_cell)->next;

    return node;
}

int get_priority(ope_data operation){
    if (operation == MUL)
    {
        return 1;
    }
    if (operation == ADD || operation == SUB)
    {
        return 0;
    }
}

syntax_tree* read_node(token_list_cell** p_cell, int cur_ope_priority){
    if (cur_ope_priority == 2)
    {
        return eat_token(p_cell);
    }

    syntax_tree* cur_node = read_node(p_cell, cur_ope_priority+1);
    if (!*p_cell)
    {
        return cur_node;
    }
    
    syntax_tree* new_node;
    while (*p_cell && get_priority(*(ope_data*) (*p_cell)->data->data) == cur_ope_priority)
    {

        new_node = eat_token(p_cell);

        new_node->left_node = cur_node;
        cur_node = new_node;

        new_node = read_node(p_cell, cur_ope_priority+1);
        cur_node->right_node = new_node;
    }

    return cur_node;
    
}

syntax_tree* read_expression(token_list* p_list){
    token_list_cell** p_cell = malloc(sizeof(token_list_cell*));
    *p_cell = p_list->first;
    syntax_tree* return_tree =  read_node(p_cell, 0);
    free(p_cell);
    return return_tree;
    
}

void print_syntax_tree(syntax_tree* tree){
    print_token(tree->root);
    putchar(' ');

    if (tree->left_node != NULL){
        print_syntax_tree(tree->left_node);
        putchar(' ');
    }

    if(tree->right_node != NULL){
        print_syntax_tree(tree->right_node);
        putchar(' ');
    }
}

void free_tree(syntax_tree* tree){
    if (tree->left_node != NULL){
        free_tree(tree->left_node);
    }

    if(tree->right_node != NULL){
        free_tree(tree->right_node);
    }
    free(tree);
}
