/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:26:00 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/04 16:25:03 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "environment.h"

t_env	*new_env_node(char *name, char *value)
{
	t_env	*node;

	node = xmalloc(sizeof(t_env));
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

	name = NULL;
	value = NULL;
	new = NULL;
	i = 0;
	while (envs[i])
	{
		name = get_env_name(envs[i]);
		if (!name)
			return (NULL);
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

// int	main(int argc, char *argv[], char *envp[])
// {
// 	(void)argc;
// 	(void)argv;
// 	t_env	*env = NULL;
// 	env = get_env(envp);
// 	if (!env)
// 		return (0);
// 	// t_env *temp = env;
// 	// while (temp)
// 	// {
// 	// 	printf("%s\t%s\n", temp->name, temp->value);
// 	// 	temp = temp->next;
// 	// }
// 	free_env_list(&env);
// 	free(env);
// 	return (0);
// }

