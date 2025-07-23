/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:26:00 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/23 14:42:56 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "environment.h"

t_env	*new_env_node(char *name, char *value)
{
	t_env	*node;

	node = xmalloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	add_env_node_back(t_env **env, t_env *current)
{
	t_env	*temp;

	if (*env == NULL)
	{
		*env = current;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = current;
}

t_env	*create_env(t_env **env, char **envs)
{
	char	*name;
	char	*value;
	t_env	*new;
	int		i;

	new = NULL;
	i = 0;
	while (envs[i])
	{
		name = NULL;
		value = NULL;
		name = get_env_name(envs[i]);
		if (!name)
			return (NULL);
			//do we also need to free the whole env here?
		value = get_env_value(envs[i]);
		if (!value)
			return (free(name), NULL);
		new = new_env_node(name, value);
		if (!new)
			return (free_env(env), NULL);
		add_env_node_back(env, new);
		i++;
	}
	return (*env);
}

// t_env	*create_export(t_env *env, t_env **export)
// {
// 	char	*name;
// 	char	*value;
// 	t_env	*new;
// 	t_env	*lowest;
// 	int		list_len;

// 	list_len = ft_listlen(env);
// 	lowest = NULL;
// 	while (list_len > 0)
// 	{
// 		if (lowest == NULL)
// 			lowest = get_lowest_node(env);
// 		else
// 			lowest = get_next_lowest_node(env, lowest);
// 		//when there is no lowest anymore it might return null, so we need to make sure with the lits we dont go over limit
// 		name = ft_strdup(lowest->name);
// 		if (!name)
// 			return (free_env(export), NULL);
// 		value = ft_strdup(lowest->value);
// 		if (!value)
// 			return (free_env(export), NULL);
// 		new = new_env_node(name, value);
// 		if (!new)
// 			return (free_env(export), NULL);
// 		add_env_node_back(export, new);
// 		list_len--;
// 	}
// 	return (*export);
// }

t_env	*get_env(char **envp)
{
	t_env	*env;
	char	**envs;

	env = NULL;
	envs = arr_dup(envp);
	if (!envs)
		return (NULL);
	create_env(&env, envs);
	free_arr(envs);
	return (env);
}
