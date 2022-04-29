#include "optimise.h"

//utility functions
void squash_l(syntax_tree** p_tree){
    syntax_tree* temp;
    temp = *p_tree;
    *p_tree = temp->right_node;
    temp->right_node = NULL;
    free_tree(temp);
}
void squash_r(syntax_tree** p_tree){
    syntax_tree* temp;
    temp = *p_tree;
    *p_tree = temp->left_node;
    temp->left_node = NULL;
    free_tree(temp);
}

void optimise_tree(syntax_tree* tree);

//assumes we are already on a "operation" node
int simplify_constants(syntax_tree** p_tree){
    int value;
    ope_data* operation = (ope_data*) (*p_tree)->root->data;
    if((*p_tree)->left_node->root->t_type == NUMBER
    && (*p_tree)->right_node->root->t_type == NUMBER){
        switch (*operation)
        {
        case ADD:
            value = ((num_data*)((*p_tree)->right_node->root->data))->value 
            + ((num_data*)((*p_tree)->left_node->root->data))->value;
            break;
        case SUB:
            value = ((num_data*)((*p_tree)->left_node->root->data))->value 
            - ((num_data*)((*p_tree)->right_node->root->data))->value;
            break;
        case MUL:
            value = ((num_data*)((*p_tree)->right_node->root->data))->value 
            * ((num_data*)((*p_tree)->left_node->root->data))->value;
            break;
        default:
            return 1;
        }

        squash_l(p_tree);
        (*p_tree)->root;
    }
    return 1;
}

//assumes we are already working on a "operation" node
int neutral_elements(syntax_tree** p_tree){
    syntax_tree* temp_tree;
    ope_data* operation = (ope_data*) (*p_tree)->root->data;
    num_data* value;
    //if we have any of : 1* , 0+, 0- on the left tree
    if((*p_tree)->left_node->root->t_type == NUMBER){
        value = (num_data*)((*p_tree)->left_node->root->data);
        if((value->value == 1 && *operation == MUL) 
        || (value->value == 0 && *operation == ADD)
        || (value->value == 0 && *operation == SUB))
        {
            //we destroy the left tree, and move its roots up
            squash_l(p_tree);
            if(*operation == SUB) { 
                //if we replace 0- by something, we also need to negate anything in the left tree
                negate_tree(*p_tree); 
            }
            return 0;
        }
    }
    // same as above, but on the right tree. Also, no special case (such as -0)
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

void negate_tree(syntax_tree* tree){
    if(tree->left_node){
        negate_tree(tree->left_node);
    }
    if(tree->right_node){
        negate_tree(tree->right_node);
    }
    if(tree->root->t_type == NUMBER){
        ((num_data*) tree->root->data)->value *= -1;
    }else if(tree->root->t_type == VARIABLE){
        ((var_data*) tree->root->data)->is_negative = true;
    }
}