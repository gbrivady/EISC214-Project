#include "token.h"

int size_of_data(token_type t_type){
    switch (t_type)
    {
    case BRACKET:
        return sizeof(bool);
    case OPERATION:
        return sizeof(ope_data);
    case VARIABLE:
        return sizeof(var_data);
    case NUMBER:
        return sizeof(num_data);
    default:
        printf("Error : Unrecognised token type.");
        exit(1);
    }
}

token* empty_token(token_type t_type, void* p_data){
    token* p_token = malloc(sizeof(token));
    if (p_token == NULL)
    {
        printf("Error : Could not allocate memory for token in empty_token");
        exit(1);
    }
    p_token->t_type = t_type;
    p_token->data = malloc(size_of_data(t_type));
    if(p_token->data == NULL){
        printf("Error : Could not allocate memory for token data in empty_token");
        exit(1);
    }
    return p_token;
}

void free_token(token* p_token){
    free(p_token->data);
    free(p_token);
}

void print_token(token* p_token){
    switch (p_token->t_type)
    {
    case BRACKET:
        print_token_bracket(p_token);
        break;
    case OPERATION:
        print_token_operation(p_token);
        break;
    case VARIABLE:
        print_token_variable(p_token);
        break;
    case NUMBER:
        print_token_number(p_token);
        break;
    default:
        printf("Error : Unrecognised token type.");
        break;
    }
}

void print_token_bracket(token* p_token){
    printf("BRACKET:");
    if (*(bool*)p_token->data)
    {
        printf("(");
    }else
    {
        printf(")");
    } 
}

void print_token_operation(token* p_token){
    printf("OPERATION:");
    switch (*(ope_data*)p_token->data)
    {
    case ADD:
        printf("+");
        break;
    case SUB:
        printf("-");
        break;
    case MUL:
        printf("*");
        break;
    default:
        printf("<?>");
        break;
    }
}

void print_token_variable(token* p_token){
    printf("VARIABLE:%s", ((var_data*)p_token->data)->name);
}

void print_token_number(token* p_token){
    printf("NUMBER:%d", ((num_data*)p_token->data)->value);
}