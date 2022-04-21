#include "token.h"

int size_of_data(token_type t_type){
    switch (t_type)
    {
    case BRACKET:
        return sizeof(token_list*);
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

token* empty_token(token_type t_type){
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
    if (p_token->t_type == VARIABLE)
    {
        free(((var_data*)p_token->data)->name);
    }
    if (p_token->t_type == BRACKET){
        free_token_list(*(token_list**)p_token->data, true);
    }
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
    printf("BRACKET:(");
    print_token_list(*((token_list**)p_token->data));
    putchar(')');
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
    printf("VARIABLE:");
    if(((var_data*)p_token->data)->is_negative){
        putchar('-');
    }
    printf("%s", ((var_data*)p_token->data)->name);
}

void print_token_number(token* p_token){
    printf("NUMBER:%d", ((num_data*)p_token->data)->value);
}


void append_token(token_list* p_list, token* p_token){
    token_list_cell* new_cell = malloc(sizeof(token_list_cell));
    new_cell->data = p_token;
    new_cell->prev = NULL;
    new_cell->next = NULL;
    if (p_list->first == NULL)
    {
        p_list->first = new_cell;
        p_list->last = new_cell;
    }else {
        new_cell->prev = p_list->last;
        p_list->last->next = new_cell;
        p_list->last = new_cell;
    }
}

void print_token_list(token_list* p_t_list){
    token_list_cell* cur_cell = p_t_list->first;
    while (cur_cell != NULL)
    {
        print_token(cur_cell->data);
        cur_cell = cur_cell->next;
    }
    
}

void free_token_list(token_list* p_t_list, bool free_content){
    token_list_cell* cur_cell = p_t_list->first;
    token_list_cell* next_cell;
    while (cur_cell != NULL)
    {
        if(free_content){
            free_token(cur_cell->data);
        }
        next_cell = cur_cell->next;
        free(cur_cell);
        cur_cell = next_cell;
    }
    free(p_t_list);
}