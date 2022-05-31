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

    //TODO : SSCANF to scan functions/reserved names
    if (isalpha(str[0]) && str[0] != '~') // then it is a variable
    {
        p_token = empty_token(VARIABLE);
        unsigned int size = 0;
        while (isalnum(str[size]))
        {
            size += 1;
        }
        var_data* p_var_data = (var_data*)(p_token->data);
        p_var_data->name = calloc(size+1, sizeof(char));
        if(p_var_data == NULL){
            printf("Error : Could not allocate memory for variable name in string_to_token");
            exit(1);
        }
        memcpy(p_var_data->name, str, size);
        p_var_data->size_name = size+1;
        p_var_data->is_negative = false;
    } else if(isdigit(str[0]) || str[0]=='~'){ // it is a number
        if (str[0]=='~')
        {
            str[0] = '-';
        }
        
        p_token = empty_token(NUMBER);
        //printf("%d \n", scanf("%d%s", str));
        num_data* token_data = ((num_data*)p_token->data);

        mpfr_init(token_data->value.x);
        mpfr_init(token_data->value.y);

        mpfr_strtofr(token_data->value.x, str, p_str, 10, MPFR_RNDN);
        mpfr_set(token_data->value.y, token_data->value.x, MPFR_RNDN);

        // token_data->value.x = strtod(str, p_str);
        // token_data->value.y = ((num_data*)p_token->data)->value.x;
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
        p_token = token_from_string(&str);
        if (p_token == NULL)
        {
            //End of an open bracket
            return t_list;
        }
        
        //shift str for next read
        switch (p_token->t_type)
        {
        case BRACKET:
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
            // while (isdigit(str[0]) || (str[0] == '.' || ))
            // {
            //     str += 1;
            // }
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