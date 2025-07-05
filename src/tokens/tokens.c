#include "../minishell.h"
#include "tokens.h"

// return (-2); for unclosed brackets
int find_token_len(char *str, bool count_quote)
{
    int count;

    count = 0;
    while (is_space(*str))
        str++;
    if (redir(str))
        return (redir(str));
    while(*str && !is_space(*str))
    {
        if (redir(str))
            break ;
        if (is_quote(*str))
        {
            if (find_quote_len(str, 0) < 0)
                return (find_quote_len(str, 0));
            count += find_quote_len(str, count_quote);
            str += find_quote_len(str, 1);
        }
        else
        {
            count++;
            str++;
        }
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
            token_len = find_token_len(str, 1);
            if (token_len < 0)
                return (token_len);
            count++;
            str += token_len;
        }
    }
    return (count);
}

void add_token(char **arr, int index, char *str)
{
    int j;
    int token_len;

    token_len = find_token_len(str, 0);
    arr[index] = (char *)malloc((token_len + 1) * sizeof(char));
    if (!arr[index])
        return ;
    
    j = 0;
    while(j < token_len)
    {
        if (str[j] == '$')
            add_env_variable(arr[index], str, &j);
        if (is_quote(str[j]))
        {
            add_quoted_sequence(arr[index], str, &j);
            str += 2;
        }
        else
        {
            arr[index][j] = str[j];
            j++;
        }
    }
    arr[index][j] = '\0';
}

char **get_tokens(char *str, t_env *env)
{
    (void)env;
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
        str += find_token_len(str, 1);
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