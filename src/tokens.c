#include "minishell.h"

bool is_quote(char c)
{
    if (c == '\'')
        return (true);
    else if (c == '\"')
        return (true);
    else
        return (false);
}

bool is_space(char c)
{
    if (c == 32)
        return (true);
    else
        return (false);
}

static int redir(char *str)
{
	if (!(*str))
		return (0);
	if (*str == '<')
	{
		str++;
		if (*str != '<')
			return (1);
		if (*str == '<')
			return (2);
	}
	else if (*str == '>')
	{
		str++;
		if (*str != '>')
			return (1);
		if (*str == '>')
			return (2);
	}
	else if (*str == '|')
		return (1);
    return (0);
}

int find_quote_len(char *str, bool count_quote) // doesnt do env vars yet
{
    int quote_type;
    int count;

    count = 0;
    quote_type = *str;
    str++;
    while (*str)
    {
        if (*str == quote_type)
            break ;
        count++;
        if (*(str + 1) == '\0')
            return (-2);
        str++;
    }
    if (count_quote)
        count += 2;
    return (count);
}

// return (-2); for unclosed brackets
int find_token_len(char *str)
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
            count += find_quote_len(str, 0);
            str += find_quote_len(str, 1) + 2;
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
            token_len = find_token_len(str);
            if (token_len < 0)
                return (token_len);
            count++;
            str += token_len;
        }
    }
    return (count);
}

void add_quoted_sequence(char *dest, char *src, int *j) // doesnt do env vars yet
{
    int quote_type;

    quote_type = src[*j];
    src++;
    while (src[*j] != quote_type)
    {
        // if (src[*j] == '$' && quote_type == '\"')
            // ;
        dest[*j] = src[*j];
        (*j)++;
    }
}

void add_token(char **arr, int index, char *str)
{
    int j;
    int token_len;

    token_len = find_token_len(str);
    arr[index] = (char *)malloc((token_len + 1) * sizeof(char));
    if (!arr[index])
        return ;
    
    j = 0;
    while(j < token_len)
    {
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
int main()
{
    char *str = "bot '12\"3\"' haha ";
    char **tokens = get_tokens(str);
    print_arr(tokens);
    fflush(NULL);
    free_arr(tokens);

}

char **get_tokens(char *str)
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