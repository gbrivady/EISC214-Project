#include "optimise.h"

void optimise_tree(syntax_tree* tree);

int simplify_constants(syntax_tree* tree);

void squash_l(syntax_tree** p_tree){
    syntax_tree* temp;
    temp = *p_tree;
    *p_tree = temp->right_node;
    temp->left_node = NULL;
    free(temp);
}
void squash_r(syntax_tree** p_tree){
    syntax_tree* temp;
    temp = *p_tree;
    *p_tree = temp->left_node;
    temp->right_node = NULL;
    free(temp);
}


int neutral_elements(syntax_tree** p_tree){
    syntax_tree* temp_tree;
    ope_data* operation = (ope_data*) (*p_tree)->root->data;
    num_data* value;
    if((*p_tree)->left_node->root->t_type == NUMBER){
        value = (num_data*)((*p_tree)->left_node->root->data);
        if((value->value == 1 && *operation == MUL) 
        || (value->value == 0 && *operation == ADD)
        || (value->value == 0 && *operation == SUB))
        {
            squash_l(p_tree);
            if(*operation == SUB) { 
                // negate_tree(tree); 
            }
            return 0;
        }
    }
    if((*p_tree)->right_node->root->t_type == NUMBER){
        value = (num_data*)((*p_tree)->right_node->root->data);
        if((value->value == 1 && *operation == MUL) 
        || (value->value == 0 && *operation == ADD)
        || (value->value == 0 && *operation == SUB))
        {
            squash_r(p_tree);
            return 0;
        }
    }
    return 1;
}

void negate_tree(syntax_tree* tree);