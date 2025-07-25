/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:07:27 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/25 21:40:14 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_executable(char *cmd)
{
	char	*full_cmd;

	full_cmd = ft_strdup(cmd);
	if (!full_cmd)
		return (NULL);
	if (access(full_cmd, F_OK) == 0)
		return (full_cmd);
	return (free(full_cmd), NULL);
}


char	*ft_getenv(t_env *env, char *key)
{
	char	*value;
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
		{
			value = ft_strdup(env->value);
			if (!value)
				return (NULL);
			return (value);
		}
		env = env->next;
	}
	return (NULL);
}

char	**get_paths(t_env *env, char *cmd)
{
	char	*path;
	char	**paths;
	char	*temp;
	int		i;

	path = ft_getenv(env, "PATH=");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (free(path), NULL);
	i = 0;
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
	return (free(path), paths);
}

char	*get_cmd(t_env *env, char *cmd)
{
	char	**paths;
	char	*full_cmd;
	int		i;

	if (cmd[0] == '/' || cmd[0] == '.')
		return (check_executable(cmd));
	i = 0;
	paths = get_paths(env, cmd);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_cmd = ft_strdup(paths[i]);
		if (!full_cmd)
			return (free_arr(paths), NULL);

		if (access(full_cmd, F_OK) == 0)
			return (free(paths), full_cmd);
		free(full_cmd);
		i++;
	}
	free_arr(paths);
	return (NULL);
}
