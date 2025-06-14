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

char	*get_cmd(char *cmd)
{
	char	**paths;
	char	*full_cmd;
	int		i;

	if (cmd[0] == '/' || cmd[0] == '.')
		return (cmd);

	i = 0;
	paths = get_paths(cmd);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_cmd = ft_strdup(paths[i]);
		if (!full_cmd)
			return (free_arr(paths), NULL);
		if (access(full_cmd, F_OK) == 0)
			return (free_arr(paths), full_cmd);
		free(full_cmd);
		i++;
	}
	free_arr(paths);
	return (NULL);
}

// int	name_length(const char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '=')
// 		break;
// 		i++;
// 	}
// 	//cause we also want to include the =
// 	return (i + 1);
// }

// t_env	*new_env_node(char *name, char *value)
// {
// 	t_env	*node;

// 	node = malloc(sizeof(t_env));
// 	if (!node)
// 		return (NULL);
// 	node->name = name;
// 	node->value = value;
// 	node->next = NULL;
// }

// void	free_env_node(t_env **env_ptr)
// {
// 	t_env	*node;

// 	if (!env_ptr || !*env_ptr)
// 		return ;
// 	node = *env_ptr;
// 	if (node->name)
// 	free(node->name);
// 	if (node->value)
// 	free(node->value);
// 	node = NULL;
// }

// void	free_env_list(t_env **env)
// {
// 	t_env	*temp;
// 	while (*env)
// 	{
// 		temp = *env;
// 		*env = (*env)->next;
// 		free_env_node(&temp);
// 	}
// 	*env = NULL;
// }

// t_env	*create_env(t_env **env, char **envp)
// {
// 	char	**envs;
// 	char	*name;
// 	char	*value;
// 	int		name_len;
// 	int		env_len;
// 	int		i;
// 	t_env	*new;

// 	envs = ft_split(envp, '\n');
// 	if (!envs)
// 		return (NULL);
// 	name = NULL;
// 	value = NULL;
// 	name_len = 0;
// 	env_len = 0;
// 	i = 0;
// 	new = NULL;
// 	while (envs[i])
// 	{
// 		name_len = name_length(envs[i]);
// 		name = ft_substr(envs[i], 0, name_len);
// 		if (!name)
// 			return (free_arr(envs), NULL);
// 		env_len = ft_strlen(envs[i]);
// 		value = ft_substr(envs[i], name_len, env_len);
// 		if (!value)
// 			return (free(name), free_arr(envs), NULL);
// 		}
// 		new = (new_env_node(name, value));
// 		if (!new)
// 			return (free_env_list(env), NULL);

// 	}
// }


