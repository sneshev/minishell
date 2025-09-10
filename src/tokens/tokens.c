/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:05:53 by sneshev           #+#    #+#             */
/*   Updated: 2025/09/10 11:22:01 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "tokens.h"

int	count_envvar(char **str, t_env *env, bool expand_envvar, int *count);

// return (-2); for unclosed brackets
int	find_token_len(char *str, t_env *env, bool count_quote, bool expand_envvar)
{
	int	count;

	count = 0;
	while (is_space(*str))
		str++;
	if (redir_or_pipe(str))
		return (redir_or_pipe(str));
	while (*str && !is_space(*str) && !redir_or_pipe(str))
	{
		if (*str == '$')
			return (count_envvar(&str, env, expand_envvar, &count));
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
int	count_tokens(char *str, t_env *env)
{
	int	count;
	int	token_len;

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
			else if (*str != '$' || find_envvar_len(str + 1, env) > 0)
				count++;
			str += token_len;
		}
	}
	return (count);
}

void	add_token(char **arr, int index, char *str, t_env *env)
{
	int	j;
	int	token_len;

	token_len = find_token_len(str, env, false, true);
	arr[index] = (char *)malloc((token_len + 1) * sizeof(char));
	if (!arr[index])
		return ;
	j = 0;
	while (j < token_len)
	{
		if (*str == '$')
		{
			str++;
			add_env_variable(arr[index], str, &j, env);
			str += find_varname_len(str);
		}
		else if (is_quote(*str))
		{
			add_quoted_sequence(arr[index], str, &j, env);
			str += find_quote_len(str, env, true, false);
		}
		else
			arr[index][j++] = *(str++);
	}
	arr[index][j] = '\0';
}

int	add_token_move_str(char **str, t_env *env, char **arr, int *index)
{
	if (is_quote(**str) || find_token_len(*str, env, 0, 1)
		|| (*index > 0 && is_redirect(arr[*index - 1])))
	{
		add_token(arr, *index, *str, env);
		(*index)++;
	}
	*str += find_token_len(*str, env, true, false);
	if (*index > 0 && !arr[*index - 1])
		return (-1);
	return (1);
}

char	**get_tokens(char *str, t_env *env, int total_tokens)
{
	char	**arr;
	int		index;

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
		if (is_heredoc(str))
		{
			if (add_heredoc_tokens(arr, &index, &str) == -1)
				return (free_arr(arr), NULL);
		}
		else
		{
			if (add_token_move_str(&str, env, arr, &index) == -1)
				return (free_arr(arr), NULL);
		}
	}
	return (arr[index] = NULL, arr);
}
