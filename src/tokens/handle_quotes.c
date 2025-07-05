#include "../minishell.h"
#include "tokens.h"

void add_env_variable(char *dest, char *src, int *j)
{
	(void)dest;
	(void)src;
	(void)j;
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

void add_quoted_sequence(char *dest, char *src, int *j) // doesnt do env vars yet
{
    int quote_type;

    quote_type = src[*j];
    src++;
    while (src[*j] != quote_type)
    {
        if (src[*j] == '$' && quote_type == '\"')
            add_env_variable(dest, src, j);
        dest[*j] = src[*j];
        (*j)++;
    }
}