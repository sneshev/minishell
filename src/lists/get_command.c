/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:07:27 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/26 15:28:53 by mmisumi          ###   ########.fr       */
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
	{
		if (is_directory(full_cmd) == true)
			return (write_err(cmd, "Is a directory"), full_cmd);
		if (access(full_cmd, X_OK) == -1)
			return (write_err(cmd, "Permission denied"), full_cmd);
		return (full_cmd);
	}
	write_err(cmd, "No such file or directory");
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
	return (ft_strdup(""));
}

char	**get_paths(t_env *env, char *cmd, int i)
{
	char	*path;
	char	**paths;
	char	*temp;

	path = ft_getenv(env, "PATH=");
	if (!path)
		return (NULL);
	if (!*path)
		return (free(path), write_err(cmd, "command not found"), NULL);
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

char	*get_cmd(t_env *env, char *cmd)
{
	char	**paths;
	char	*full_cmd;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (check_executable(cmd));
	i = 0;
	paths = get_paths(env, cmd, 0);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full_cmd = ft_strdup(paths[i]);
		if (!full_cmd)
			return (free_arr(paths), NULL);
		if (access(full_cmd, F_OK) == 0)
		{
			if (access(full_cmd, X_OK) == -1)
				write_err(cmd, "Permission denied");
			return (free_arr(paths), full_cmd);
		}
		i++;
		free(full_cmd);
	}
	return (write_err(cmd, "command not found"), free_arr(paths), NULL);
}
