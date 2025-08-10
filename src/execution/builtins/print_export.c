/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:51:27 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/10 12:23:31 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../execution.h"

int	ft_envlen(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

t_env	*get_next_lowest_node(t_env *env, t_env *lowest)
{
	t_env	*cur;

	cur = NULL;
	while (env)
	{
		if (ft_strcmp(env->name, lowest->name) > 0)
		{
			if (cur == NULL || ft_strcmp(cur->name, env->name) > 0)
				cur = env;
		}
		env = env->next;
	}
	return (cur);
}

t_env	*get_lowest_node(t_env *env)
{
	t_env	*lowest;

	lowest = env;
	while (env)
	{
		if (ft_strcmp(lowest->name, env->name) > 0)
			lowest = env;
		env = env->next;
	}
	return (lowest);
}

void	print_export(t_env *env)
{
	const char	*s = "declare -x";
	t_env		*lowest;
	t_env		*next_lowest;
	int			env_len;

	env_len = ft_envlen(env);
	lowest = get_lowest_node(env);
	printf("%s %s\"%s\"\n", s, lowest->name, lowest->value);
	while (env_len > 1)
	{
		next_lowest = get_next_lowest_node(env, lowest);
		lowest = next_lowest;
		printf("%s %s\"%s\"\n", s, lowest->name, lowest->value);
		env_len--;
	}
}
