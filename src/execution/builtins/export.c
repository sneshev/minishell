/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:26:29 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/10 11:56:16 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../execution.h"

t_env	*create_new_variable(t_env **env, char *arg, char *name)
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

t_env	*replace_env_value(t_env *env, char *arg, char *name, int index)
{
	char	*value;
	int		i;

	i = 0;
	while (i < index)
	{
		env = env->next;
		i++;
	}
	if (is_without_value(name) == true)
		return (env);
	if (is_without_value(env->name) == true)
		update_name(env);
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
			replace_env_value(*env, list->args[i], name, index);
		else
			create_new_variable(env, list->args[i], name);
		free(name);
		i++;
	}
	return (0);
}
