#include "../minishell.h"
#include "tokens.h"

// return (-2); for unclosed brackets
int find_token_len(char *str, t_env *env, bool count_quote, bool expand_envvar)
{
    (void)expand_envvar;
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
        if (*str == '$')
        {
            str++;
            if (expand_envvar)
                count += find_envvar_len(str, env);
            else
                count += 1 + find_varname_len(str);
            str += find_varname_len(str);
        }
        else if (is_quote(*str))
        {
            if (find_quote_len(str, env, 0, false) < 0)
                return (find_quote_len(str, env, 0, false));
            count += find_quote_len(str, env, count_quote, expand_envvar);
            str += find_quote_len(str, env, 1, false);
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
            token_len = find_token_len(str, NULL, true, false);
            if (token_len < 0)
                return (token_len);
            count++;
            str += token_len;
        }
    }
    return (count);
}

void add_token(char **arr, int index, char *str, t_env *env)
{
    int j;
    int token_len;

    token_len = find_token_len(str, env, false, true);
    arr[index] = (char *)malloc((token_len + 1) * sizeof(char));
    if (!arr[index])
        return ;
    
    j = 0;
    while(j < token_len)
    {
        if (*str == '$')
        {
            str++;
            add_env_variable(arr[index], str, &j, env);
            str += find_varname_len(str);
        }
        else if (is_quote(*str))
        {
            add_quoted_sequence(arr[index], str, &j, env); // do &str
            str += find_quote_len(str, env, true, false);
        }
        else
        {
            arr[index][j] = *str;
            j++;
            str++;
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
        add_token(arr, index, str, env);
        str += find_token_len(str, env, true, false);
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