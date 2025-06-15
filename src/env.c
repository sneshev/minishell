/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:07:27 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/13 16:57:54 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char *cmd)
{
	char	*path;
	char	**paths;
	char	*temp;
	int		i;

	i = 0;
	path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (free(path), NULL);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (free(path), free_arr(paths), NULL);
		free(paths[i]);
		paths[i] = ft_strjoin(temp, cmd);
		if (!paths[i])
			return (free(temp), free(path), free_arr(paths), NULL);
		free(temp);
		i++;
	}
	return (paths);
}

// char	*get_cmd(char *cmd)
// {
// 	char	**paths;
// 	char	*full_cmd;
// 	int		i;

// 	if (cmd[0] == '/' || cmd[0] == '.')
// 		return (cmd);

// 	i = 0;
// 	paths = get_paths(cmd);
// 	if (!paths)
// 		return (NULL);
// 	while (paths[i])
// 	{
// 		full_cmd = ft_strdup(paths[i]);
// 		if (!full_cmd)
// 			return (free_arr(paths), NULL);
// 		if (access(full_cmd, F_OK) == 0)
// 			return (free_arr(paths), full_cmd);
// 		free(full_cmd);
// 		i++;
// 	}
// 	free_arr(paths);
// 	return (NULL);
// }

int	name_length(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		break;
		i++;
	}
	//cause we also want to include the =
	return (i + 1);
}

t_env	*new_env_node(char *name, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	free_env_node(t_env **env_ptr)
{
	t_env	*node;

	if (!env_ptr || !*env_ptr)
		return ;
	node = *env_ptr;
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	node = NULL;
}

void	free_env_list(t_env **env)
{
	t_env	*temp;
	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free_env_node(&temp);
	}
	*env = NULL;
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

int	arr_length(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**arr_dup(char **arr)
{
	char	**dup;
	int		arr_len;
	int		index;

	arr_len = arr_length(arr);
	dup = malloc(sizeof(char *) *(arr_len + 1));
	if (!dup)
		return (NULL);
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
		new = (new_env_node(name, value));
		if (!new)
			return (free_env_list(env), NULL);
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
	print_arr(envs);
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
// 	t_env *temp = env;
// 	while (temp)
// 	{
// 		printf("name: %s\tvalue: %s\n", temp->name, temp->value);
// 		temp = temp->next;
// 	}
// 	free_env_list(&env);
// 	return (0);
// }


