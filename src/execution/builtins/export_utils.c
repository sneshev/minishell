/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:10:15 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/25 13:36:13 by mmisumi          ###   ########.fr       */
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

bool	existing_key(t_env **env, char *key)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strncmp(temp->name, key, ft_strlen(key)) == 0
			&& temp->name[ft_strlen(key)] == '=')
			return (true);
		temp = temp->next;
	}
	return (false);
}

//checks if the key has a value (doesnt matter if it has '=' or not)
bool	check_empty_keyvalue(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=' && arg[i + 1])
			return (false);
		i++;
	}
	return (true);
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
