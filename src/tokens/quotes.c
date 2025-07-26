/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:12:06 by sneshev           #+#    #+#             */
/*   Updated: 2025/07/26 13:01:37 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "tokens.h"

int	find_quote_len(
	char *str, t_env *env, bool count_quote, bool expand_envvar)
{
	int	quote_type;
	int	count;

	count = 0;
	quote_type = *str;
	if (quote_type == '\'')
		expand_envvar = false;
	str++;
	while (*str)
	{
		if (*str == quote_type)
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
		else
		{
			count++;
			str++;
		}
		if (!(*str))
			return (-2);
	}
	if (count_quote)
		count += 2;
	return (count);
}

void	add_quoted_sequence(char *dest, char *src, int *j, t_env *env)
{
	int	quote_type;

	quote_type = *src;
	src++;
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
