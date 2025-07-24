/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:26:29 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/24 16:41:58 by mmisumi          ###   ########.fr       */
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

t_env	*export_empty_key(t_env **env, t_env *cur, char *name)
{
	t_env	*new;
	char	*value;

	value = ft_strdup("");
	if (!value)
		return (NULL);
	new = NULL;
	if (cur == NULL)
	{
		if (existing_key(env, name) == true)
			return (free(value), NULL);
		new = new_env_node(name, value);
		if (!new)
			return (free(value), NULL);
		add_env_node_back(env, new);
	}
	else
	{
		if (cur->value)
			free(cur->value);
		cur->value = value;
	}
	return (*env);
}

t_env	*create_new_variable(t_env **env, char *arg, char *name)
{
	t_env	*new;
	char	*key;
	char	*value;

	key = ft_strdup(name);
	if (!key)
		return (NULL);
	if (check_empty_keyvalue(arg) == true)
		return(export_empty_key(env, NULL, key));
	value = get_env_value(arg);
	if (!value)
		return (free(key), NULL);
	new = new_env_node(key, value);
	if (!new)
		return (free(key), free(value), NULL);
	add_env_node_back(env, new);
	return (*env);
}

t_env	*replace_env_value(t_env **env, char *arg, char *name)
{
	t_env	*cur;
	t_env	*prev;
	char	*value;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			if (check_empty_keyvalue(arg) == true)
				return (export_empty_key(env, cur, name));
			value = get_env_value(arg);
			if (!value)
				return (NULL);
			if (cur->value)
				free(cur->value);
			cur->value = value;
			return (cur);
		}
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

int	execute_export(t_list *list, t_env **env)
{
	char	*name;
	int		i;

	if (!list->args[1])
		print_export(*env);
	i = 1;
	while (list->args[i])
	{
		name = get_env_name(list->args[i]);
		if (!name)
			return (-1);
		if (validate_export_syntax(name) == false)
		{
			write_err("export: not an identifier", name);
			return (free(name), 1);
		}
		if (replace_env_value(env, list->args[i], name) == NULL)
			create_new_variable(env, list->args[i], name);
		free(name);
		i++;
	}
	return (0);
}
