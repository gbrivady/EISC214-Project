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
    if (operation == MUL || operation == DIV)
    {
        return 1;
    }
    if (operation == ADD || operation == SUB)
    {
        return 0;
    }
}

/**
 * @brief Handles the read of successive operations, while maintaining correct priority orders.
 * Explained in another file.
 * 
 * @param p_cell 
 * @param cur_ope_priority 
 * @return syntax_tree* 
 */
syntax_tree* read_node(token_list_cell** p_cell, int cur_ope_priority){
    if (cur_ope_priority == MAX_PRIORITY)
    {
        return eat_token(p_cell);
    }

    syntax_tree* cur_node = read_node(p_cell, cur_ope_priority+1);
    if (!*p_cell) //we have reached the end of the token list
    {
        return cur_node;
    }
    
    syntax_tree* new_node;
    //While the operation encountered have the same priority, operation priority is from left to right
    while (*p_cell && get_priority(*(ope_data*) (*p_cell)->data->data) == cur_ope_priority)
    {

        //Creates a new node with current token
        new_node = eat_token(p_cell);

        //This token is more to the right in the expression : as such, the current node need
        //to be evaluated prior to the new node, so we put the current node as the left leaf.
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

void print_syntax_tree_core(syntax_tree* tree, int depth, int* rec)
{
    int i;
    if(tree == NULL){
        return;
    }
    printf("\t");
    for(int i = 0; i < depth; i++){
        if(i == depth - 1){
            printf("%s\u2014\u2014\u2014",rec[depth-1]?"\u0371":"\u221F");
        }
        else
            printf("%s   ",rec[i]?"\u23B8":"  ");
    }
    print_token(tree->root);
    putchar('\n');
    rec[depth]=1;
    print_syntax_tree_core(tree->left_node,depth+1, rec);
    rec[depth]=0;
    print_syntax_tree_core(tree->right_node,depth+1, rec);
}

void print_syntax_tree(syntax_tree* tree){
    //buffer for tabulations
    int rec[1006];
    print_syntax_tree_core(tree, 0, rec);
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
