/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:26:03 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/04 16:25:10 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "environment.h"

int	name_length(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			i++;
			break;
		}
		i++;
	}
	//cause we also want to include the =
	return (i);
}

int	arr_length(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*get_env_name(char *env)
{
	char	*name;
	int		name_len;

	name_len = name_length(env);
	name = ft_substr(env, 0, name_len);
	return (name);
}


char	*get_env_value(char *env)
{
	char	*value;
	int		name_len;
	int		env_len;

	name_len = name_length(env);
	env_len = ft_strlen(env);
	value = ft_substr(env, name_len, env_len);
	return (value);
}


char	**arr_dup(char **arr)
{
	char	**dup;
	int		arr_len;
	int		index;

	arr_len = arr_length(arr);
	dup = xmalloc(sizeof(char *) *(arr_len + 1));
	index = 0;
	while (arr[index])
	{
		dup[index] = ft_strdup(arr[index]);
		if (!dup[index])
			return (free_arr(dup), NULL);
		index++;
	}
	dup[index] = NULL;
	return (dup);
}