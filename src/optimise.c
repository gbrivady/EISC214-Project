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
//Does in advance operations on constants
int simplify_constants(syntax_tree** p_tree){
    int value;
    int value_l;
    int value_r;
    ope_data* operation = (ope_data*) (*p_tree)->root->data;
    if((*p_tree)->left_node->root->t_type == NUMBER
    && (*p_tree)->right_node->root->t_type == NUMBER){
        value_l = ((num_data*)((*p_tree)->left_node->root->data))->value;
        value_r = ((num_data*)((*p_tree)->right_node->root->data))->value;
        switch (*operation)
        {
        case ADD:
            value = value_l + value_r;
            break;
        case SUB:
            value = value_l - value_r;
            break;
        case MUL:
            value = value_l * value_r;
            break;
        default:
            return 0;
        }

        // We remove the operation node, and one number
        // Then we move the second number and replace its value ( for memory management )
        squash_l(p_tree);
        ((num_data*)(*p_tree)->root->data)->value = value;
        return 1;
    }
    return 0;
}

//assumes we are already working on a "operation" node
// Removes operations : 0 - [tree], [tree] - 0, 0 + [tree], and 1 * [tree]
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


//Multiplies everything in the tree by -1
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
        ((var_data*) tree->root->data)->is_negative = !((var_data*) tree->root->data)->is_negative;
    }
}