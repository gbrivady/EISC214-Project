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

void optimise_tree(syntax_tree** p_tree){
    if (((*p_tree)->root->t_type == NUMBER) || ((*p_tree)->root->t_type == VARIABLE))
    {
        return;
    }

    if ((*p_tree)->left_node)
    {
        optimise_tree(&(*p_tree)->left_node);
    }
    if((*p_tree)->right_node){
        optimise_tree(&(*p_tree)->right_node);
    }
    neutral_elements(p_tree);
    if ((*p_tree)->root->t_type == NUMBER){
        return;
    }
    simplify_constants(p_tree);
    return;
}

//assumes we are already on a "operation" node
//Does in advance operations on constants
void simplify_constants(syntax_tree** p_tree){
    range value;
    range value_l;
    range value_r;
    if((*p_tree)->left_node->root->t_type == NUMBER
    && (*p_tree)->right_node->root->t_type == NUMBER){
        ope_data* operation = (ope_data*) (*p_tree)->root->data;

        value_l = ((num_data*)((*p_tree)->left_node->root->data))->value;
        value_r = ((num_data*)((*p_tree)->right_node->root->data))->value;
        switch (*operation)
        {
        case ADD:
            value = add_range(value_l, value_r);
            break;
        case SUB:
            value = sub_range(value_l, value_r);
            break;
        case MUL:
            value = mul_range(value_l, value_r);
            break;
        case DIV:
            value = div_range(value_l, value_r);
            break;
        default:
            return;
        }

        // We remove the operation node, and one number
        // Then we move the second number and replace its value ( for memory management )
        squash_l(p_tree);
        ((num_data*)(*p_tree)->root->data)->value = value;
        return;
    }
    return;
}

// Removes operations : 0 - [tree], [tree] - 0, 0 + [tree], and 1 * [tree]
void neutral_elements(syntax_tree** p_tree){
    syntax_tree* temp_tree;
    ope_data* operation; 
    num_data* value;
    //if we have any of : 1* , 0+, 0- on the left tree
    if((*p_tree)->left_node->root->t_type == NUMBER){
        operation = (ope_data*) (*p_tree)->root->data;
        value = (num_data*)((*p_tree)->left_node->root->data);
        if((value->value.x == 1 && *operation == MUL) 
        || (value->value.x == 0 && *operation == ADD)
        || (value->value.x == 0 && *operation == SUB))
        {
            //we destroy the left tree, and move its roots up
            squash_l(p_tree);
            if(*operation == SUB) { 
                //if we replace 0- by something, we also need to negate anything in the left tree
                negate_tree(*p_tree); 
            }
            return;
        }
    }
    // same as above, but on the right tree. Also, no special case (such as -0)
    if((*p_tree)->right_node->root->t_type == NUMBER){
        operation = (ope_data*) (*p_tree)->root->data;
        value = (num_data*)((*p_tree)->right_node->root->data);
        if((value->value.x == 1 && *operation == MUL) 
        || (value->value.x == 0 && *operation == ADD)
        || (value->value.x == 0 && *operation == SUB))
        {
            squash_r(p_tree);
            return;
        }
    }
    return;
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
        ((num_data*) tree->root->data)->value = negate_range(((num_data*) tree->root->data)->value);
    }else if(tree->root->t_type == VARIABLE){
        ((var_data*) tree->root->data)->is_negative = !((var_data*) tree->root->data)->is_negative;
    }
}