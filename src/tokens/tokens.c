#include "../minishell.h"
#include "tokens.h"

// return (-2); for unclosed brackets
int find_token_len(char *str)
{
    int count;
    int quote_type;

    count = 0;
    while (is_space(*str))
        str++;
    if (redir(str))
        return (redir(str));
    while(*str && !is_space(*str))
    {
        count++;
        if (is_quote(*str))
        {
            quote_type = *str;
            while (*(++str))
            {
                count++;
                if (*str == quote_type)
                    break ;
                if (*(str + 1) == '\0')
                    return (-2);
            }
        }
        str++;
        if (redir(str))
            break ;
    }
    return (count);
}

// return (-2); for unclosed brackets
int count_tokens(char *str)
{
    int count;
    int token_len;

    if (!str)
        return (-1);
    count = 0;
    while (*str)
    {
        while (is_space(*str))
            str++;
        if (*str)
        {
            token_len = find_token_len(str);
            if (token_len < 0)
                return (token_len);
            count++;
            str += token_len;
        }
    }
    return (count);
}

void add_token(char **arr, int index,char *str)
{
    int j;
    int token_len;

    token_len = find_token_len(str);
    arr[index] = (char *)xmalloc((token_len + 1) * sizeof(char));
    
    j = 0;
    while(j < token_len)
    {
        arr[index][j] = str[j];
        j++;
    }
    arr[index][j] = '\0';
}

char **get_tokens(char *str, t_env *env)
{
    char **arr = NULL;
    int total_tokens;
    int index;

    total_tokens = count_tokens(str);
    if (total_tokens < 0)
        return (printf("unclosed quotes\n"), NULL);
    arr = (char **)malloc((total_tokens + 1) * sizeof(char *));
    if (!arr)
        return (NULL);
    index = 0;
    while (index < total_tokens)
    {
        while (is_space(*str))
            str++;
        add_token(arr, index, str);
        str += find_token_len(str);
        if (!arr[index])
        {
            free_arr(arr);
            return (NULL);
        }
        index++;
    }
    arr[index] = NULL;
    return (arr);
}