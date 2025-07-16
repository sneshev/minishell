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

bool    is_valid_syntax(char **tokens)
{
    int i;

    i = 0;
	if (is_pipe(tokens[i]))
		return (false);
	while (tokens[i])
	{
		if (is_pipe(tokens[i]) && is_pipe(tokens[i + 1]))
		{
			perror_message(tokens[i]);
			return (false);
		}
		if (is_redirect(tokens[i]) && is_redirect(tokens[i + 1]))
			return (false);
		// im not sure if were supposed to take care of uncomplete commands
		if (tokens[i + 1] == NULL)
		{
			if (is_pipe(tokens[i]) || is_redirect(tokens[i]))
				return (false);
		}
		i++;
	}
	return (true);
}