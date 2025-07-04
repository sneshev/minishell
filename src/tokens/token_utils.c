#include "../minishell.h"
#include "tokens.h"

bool is_quote(char c)
{
    if (c == '\'')
        return (true);
    else if (c == '\"')
        return (true);
    else
        return (false);
}

int redir(char *str)
{
	if (!(*str))
		return (-1);
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