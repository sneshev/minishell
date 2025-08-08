/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:26:29 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/25 13:36:22 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../execution.h"

void	print_export(t_env *env)
{
	const char	*s = "declare -x";
	t_env		*lowest;
	t_env		*next_lowest;
	int			env_len;

	env_len = ft_envlen(env);
	lowest = get_lowest_node(env);
	printf("%s %s%s\n", s, lowest->name, lowest->value);
	while (env_len > 1)
	{
		next_lowest = get_next_lowest_node(env, lowest);
		lowest = next_lowest;
		printf("%s %s%s\n", s, lowest->name, lowest->value);
		env_len--;
	}
}

t_env 	*create_new_variable(t_env **env, char *arg, char *name)
{
	t_env	*new;
	char	*name_copy;
	char	*value;

	name_copy = ft_strdup(name);
	if (!name_copy)
		return (NULL);
	value = get_env_value(arg);
	if (!value)
		return (free(name_copy), NULL);
	new = new_env_node(name_copy, value);
	if (!new)
		return (free(name_copy), free(value), NULL);
	add_env_node_back(env, new);
	return (*env);
}

t_env	*replace_env_value(t_env *env, char *arg, int index)
{
	char	*value;
	char	*new_name;
	int		i;

	i = 0;
	while (i < index)
	{
		env = env->next;
		i++;
	}
	if (env->name[ft_strlen(env->name ) - 1] != '=')
	{
		new_name = ft_strjoin(env->name, "=");
		if (!new_name)
			return (NULL);
		free(env->name);
		env->name = new_name;
	}
	value = get_env_value(arg);
	if (!value)
		return (NULL);
	if (env->value)
		free(env->value);
	env->value = value;
	return (env);
}

int	execute_export(t_list *list, t_env **env)
{
	char	*name;
	int		i;
	int		index;

	if (!list->args[1])
		print_export(*env);
	i = 1;
	while (list->args[i])
	{
		name = get_env_name(list->args[i]);
		if (!name)
			return (-1);
		if (validate_export_syntax(name) == false)
			return (free(name), 1);
		index = existing_name(*env, name);
		if (index != -1)
			replace_env_value(*env, list->args[i], index);
		else
			create_new_variable(env, list->args[i], name);
		free(name);
		i++;
	}
	return (0);
}
