/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 12:51:44 by sneshev           #+#    #+#             */
/*   Updated: 2025/08/11 21:00:42 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "tokens.h"

int	redir_or_pipe(char *str)
{
	if (!str || !(*str))
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

void	write_syntax_err(char *c)
{
	write(2, "syntax error near unexpected token ", 35);
	write(2, "`", 1);
	write(2, c, ft_strlen(c));
	write(2, "'", 1);
	write(2, "\n", 1);
	set_exit_code(2);
}

bool	is_valid_syntax(char **tokens)
{
	int	i;

	i = 0;
	if (is_pipe(tokens[0]))
		return (write_syntax_err("|"), (false));
	while (tokens[i])
	{
		if (redir_or_pipe(tokens[i]) && is_pipe(tokens[i + 1]))
			return (write_syntax_err(tokens[i + 1]), false);
		if (is_redirect(tokens[i]) && redir_or_pipe(tokens[i + 1]))
			return (write_syntax_err(tokens[i + 1]), false);
		if (tokens[i + 1] == NULL)
		{
			if (is_pipe(tokens[i]) || is_redirect(tokens[i]))
				return (write_syntax_err("newline"), false);
		}
		i++;
	}
	return (true);
}

static int	find_heredoc_token_len(char *str, int len, char quote_type)
{
	while (*str && !is_space(*str))
	{
		if (is_redirect(str) || is_pipe(str))
			break ;
		if (is_quote(*str))
		{
			len++;
			quote_type = *str;
			while (*++str != quote_type)
			{
				if (!*str)
					return (printf("unclosed quotes"), -2);
				len++;
			}
		}
		len++;
		str++;
	}
	return (len);
}

int	add_heredoc_tokens(char *arr[], int *index, char **str)
{
	char	*token;
	int		len;

	token = ft_strdup("<<");
	if (!token)
		return (-1);
	arr[*index] = token;
	*index += 1;
	*str += 2;
	while (**str && is_space(**str))
		*str += 1;
	if (!**str || is_redirect(*str) || is_pipe(*str))
		return (1);
	len = find_heredoc_token_len(*str, 0, 0);
	arr[*index] = (char *)malloc(len * sizeof(char) + 1);
	if (arr[*index] == NULL)
		return (-1);
	ft_strlcpy(arr[*index], *str, (size_t)len + 1);
	*str += len;
	*index += 1;
	return (1);
}
