#include "input.h"

token* token_from_string(char** p_str){
    char* str = *p_str;
    token* p_token;
    void* token_data;
    // handles single char tokens : operation and brackets
    switch (str[0])
    {
    case '(':
        p_token = empty_token(BRACKET);
        *(token_list**)(p_token->data) = read_tokens(str+1);
        break;
    case ')':
        return NULL;
    case '+':
        p_token = empty_token(OPERATION);
        *(ope_data*)(p_token->data) = ADD;
        break;
    case '-' :
        p_token = empty_token(OPERATION);
        *(ope_data*)(p_token->data) = SUB;
        break;
    case '*' :
        p_token = empty_token(OPERATION);
        *(ope_data*)(p_token->data) = MUL;
        break;
    case '/' :
        p_token = empty_token(OPERATION);
        *(ope_data*)(p_token->data) = DIV;
        break;
    }

    if (isalpha(str[0]) && str[0] != '~') // then it is a variable
    {
        p_token = empty_token(VARIABLE);

        //Count number of characters in variable name
        unsigned int size = 0;
        while (isalnum(str[size]))
        {
            size += 1;
        }
        var_data* p_var_data = (var_data*)(p_token->data);

        //Allocates memory for the name in token data
        p_var_data->name = calloc(size+1, sizeof(char));
        if(p_var_data == NULL){
            printf("Error : Could not allocate memory for variable name in string_to_token");
            exit(1);
        }
        //Copy the name into the token data
        memcpy(p_var_data->name, str, size);
        p_var_data->size_name = size+1;
        p_var_data->is_negative = false;

    } else if(isdigit(str[0]) || str[0]=='~'){ // it is a number
        if (str[0]=='~') //Special character for negative numbers
        {
            str[0] = '-';
        }
        
        p_token = empty_token(NUMBER);
        num_data* token_data = ((num_data*)p_token->data);

        //Init both values, read from string into lower bound and then copy it into upper bound
        mpfr_init(token_data->value.x);
        mpfr_init(token_data->value.y);

        mpfr_strtofr(token_data->value.x, str, p_str, 10, MPFR_RNDN);
        mpfr_set(token_data->value.y, token_data->value.x, MPFR_RNDN);
    }
    
    return p_token;
}

token_list* read_tokens(char* str){
    token* p_token;
    token_list* t_list = malloc(sizeof(token_list));
    t_list->first = NULL;
    t_list->last = NULL;
    int bracket_depth = 0;

    while (str != NULL && *str == ' ') // skip spaces at start
    {
        str += 1;
    }
    while (str != NULL && *str != '\0') 
    {
        //Reads token
        p_token = token_from_string(&str);
        if (p_token == NULL)
        {
            //The end of an open bracket has been reached
            return t_list;
        }
        
        //shift string for next read
        switch (p_token->t_type)
        {
        case BRACKET: //moves character by character to the end of the bracketed expression
            bracket_depth = 1;
            str += 1;
            while (bracket_depth != 0)
            {
                if (*str == '(')
                {
                    bracket_depth += 1;
                }
                if (*str == ')'){
                    bracket_depth -=1;
                }
                str += 1;
            }
            
            break;
        case OPERATION:
            str += 1;
            break;
        case VARIABLE:
            //one less, as the \0 at the end does not exist in the string
            str += ((var_data*)p_token->data)->size_name-1;
            break;
        case NUMBER:
            // string is already shifted inside of token_from_string
            break;
        default:
            break;
        }
        append_token(t_list, p_token);
        while (str != NULL && *str == ' ') // skip spaces after token
        {
            str += 1;
        }
    }
    
    return t_list;
}