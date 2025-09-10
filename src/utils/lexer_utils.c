/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:35:19 by sneshev           #+#    #+#             */
/*   Updated: 2025/09/10 14:40:03 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../tokens/tokens.h"

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	else
		return (false);
}

int	word_count(char const *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0')
		{
			j++;
			while (s[i] != ' ' && s[i] != '\0')
				i++;
		}
	}
	return (j);
}

// MUST BE NULL TERMINATED
int	count_strings(char **arr, bool count_empty)
{
	int		count;
	size_t	i;

	if (!arr)
		return (-1);
	count = 0;
	i = 0;
	while (arr[i])
	{
		if (*(arr[i]))
			count++;
		else if (count_empty)
			count++;
		i++;
	}
	return (count);
}

bool	is_empty_token(char *str, t_env *env)
{
	if (*str == '$')
	{
		str++;
		if (find_envvar_len(str, env) > 0)
			return (false);
		str += find_varname_len(str);
		if (!*str || is_space(*str))
			return (true);
	}
	return (false);
}
