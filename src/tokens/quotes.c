/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:12:06 by sneshev           #+#    #+#             */
/*   Updated: 2025/09/10 14:15:43 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "tokens.h"

#define PIPE -1
#define RED_IN -2
#define HEREDOC -3
#define RED_OUT -4
#define RED_APPEND -5

int	count_envvar(char **str, t_env *env, bool expand_envvar, int *count);

int	quoted_redir_len(char *str, int quote_type, int redir)
{
	if (*str == redir)
	{
		str++;
		if (*str == quote_type)
			return (1);
		else if (*str == redir)
		{
			str++;
			if (*str == quote_type)
				return (2);
		}
	}
	return (0);
}

int	is_quoted_redir_or_pipe(char *str, int quote_type, bool str_flag)
{
	int	res;

	res = 0;
	if (!str_flag)
		res = 1;
	if (*str == '|')
	{
		str++;
		if (*str == quote_type)
			return (res + 1);
	}
	else if (quoted_redir_len(str, quote_type, '<'))
		return (res + quoted_redir_len(str, quote_type, '<'));
	else if (quoted_redir_len(str, quote_type, '>'))
		return (res + quoted_redir_len(str, quote_type, '>'));
	return (0);
}

int	find_quote_len(
	char *str, t_env *env, bool count_quote, bool expand_envvar)
{
	int	quote_type;
	int	count;

	count = 0;
	if (count_quote)
		count += 2;
	quote_type = *str;
	if (quote_type == '\'')
		expand_envvar = false;
	str++;
	if (is_quoted_redir_or_pipe(str, quote_type, count_quote))
		return (is_quoted_redir_or_pipe(str, quote_type, count_quote) + count);
	while (*str != quote_type)
	{
		if (!(*str))
			return (-2);
		if (*str == '$')
			count_envvar(&str, env, expand_envvar, &count);
		else
		{
			count++;
			str++;
		}
	}
	return (count);
}

void	add_quoted_redir_or_pipe(char *dest, char *src, int *j, int quote_type)
{
	dest[*j] = -1;
	(*j)++;
	while (*src != quote_type)
	{
		dest[*j] = *src;
		src++;
		(*j)++;
	}
}

void	add_quoted_sequence(char *dest, char *src, int *j, t_env *env)
{
	int	quote_type;

	quote_type = *src;
	src++;
	if (is_quoted_redir_or_pipe(src, quote_type, 0))
	{
		add_quoted_redir_or_pipe(dest, src, j, quote_type);
		return ;
	}
	while (*src != quote_type)
	{
		if (*src == '$' && quote_type == '\"')
		{
			src++;
			add_env_variable(dest, src, j, env);
			src += find_varname_len(src);
		}
		else
		{
			dest[*j] = *src;
			src++;
			(*j)++;
		}
	}
}
