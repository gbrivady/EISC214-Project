#include "input.h"

token* token_from_string(char* str){
    token* p_token;
    void* token_data;
    // handles single char tokens : operation and brackets
    switch (str[0])
    {
    case '(':
        p_token = empty_token(BRACKET);
        *(bool*)(p_token->data) = true;
        break;
    case ')':
        p_token = empty_token(BRACKET);
        *(bool*)(p_token->data) = false;
        break;
    case '+':
        p_token = empty_token(OPERATION);
        *(ope_data*)(p_token->data) = ADD;
        return p_token;
    case '-' :
        p_token = empty_token(OPERATION);
        *(ope_data*)(p_token->data) = SUB;
        break;
    case '*' :
        p_token = empty_token(OPERATION);
        *(ope_data*)(p_token->data) = MUL;
        break;
    }

    //TODO : SSCANF to scan functions/reserved names
    if (isalpha(str[0])) // then it is a variable
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
    } else if(isdigit(str[0])){ // it is a number
         p_token = empty_token(NUMBER);
         //printf("%d \n", scanf("%d%s", str));
         ((num_data*)p_token->data)->value = strtol(str, &str, 10);
    }
    
    return p_token;
}

token_list* read_tokens(char* str){
    token* p_token;
    token_list* t_list = malloc(sizeof(token_list));
    t_list->first = NULL;
    t_list->last = NULL;

    while (str != NULL && *str == ' ') // skip spaces at start
    {
        str += 1;
    }
    while (str != NULL && *str != '\0') 
    {
        p_token = token_from_string(str);
        //shift str for next read
        switch (p_token->t_type)
        {
        case BRACKET:
            str += 1;
            break;
        case OPERATION:
            str += 1;
            break;
        case VARIABLE:
            str += ((var_data*)p_token->data)->size_name;
            break;
        case NUMBER:
            //str shift is already done in strtol within token_from_string
            while (isdigit(str[0]))
            {
                str += 1;
            }
            //no it is not you idiot
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