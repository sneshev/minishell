/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:10:15 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/08 18:19:02 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../execution.h"

void	write_export_err(char *s)
{
	write(2, "export: ", 8);
	write(2, "`", 1);
	write(2, s, ft_strlen(s));
	write(2, "'", 1);
	write(2, ": not a valid identifier", 24);
	write(2, "\n", 1);
}

bool	validate_export_syntax(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (false);
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (write_export_err(cmd), false);
	i++;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (write_export_err(cmd), false);
		i++;
	}
	return (true);
}

int	existing_name(t_env *env, char *name)
{
	int	i;

	i = 0;
	while (env)
	{
		if ((ft_strcmp(env->name, name) == 0)
			|| (ft_strncmp(env->name, name, ft_strlen(env->name)) == 0 && name[ft_strlen(env->name)] == '=')
			|| (ft_strncmp(name, env->name, ft_strlen(name)) == 0 && env->name[ft_strlen(name)] == '='))
		{
			return (i);
		}
		i++;
		env = env->next;
	}
	return (-1);
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
