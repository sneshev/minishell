/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:06:52 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/10 12:03:53 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

int	count_env_vars(t_env *env)
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

char	**convert_env(t_env *env)
{
	int		vars;
	char	**environment;
	int		i;

	if (!env)
		return (NULL);
	vars = count_env_vars(env);
	environment = malloc(sizeof(char *) * (vars + 1));
	if (!environment)
		return (NULL);
	i = 0;
	while (env)
	{
		environment[i] = ft_strjoin(env->name, env->value);
		if (!environment[i])
			return (free_arr(environment), NULL);
		i++;
		env = env->next;
	}
	environment[i] = NULL;
	return (environment);
}
