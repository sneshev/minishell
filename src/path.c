/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:07:27 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/04 15:38:47 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_env(char **envp)
// {
// 	char	*env;
// 	int		i;

// 	env = NULL;
// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
// 		{
// 			env = envp[i] + 5;
// 			if (!env)
// 				perror("no env message\n");
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (env);
// }

// char	**get_path(char *path, char *cmd)
// {
// 	char	**paths;
// 	char	*temp;
// 	int		i;

// 	i = 0;
// 	paths = ft_split(path, ':');
// 	while (paths[i])
// 	{
// 		temp = ft_strjoin(paths[i], "/");
// 		free(paths[i]);
// 		paths[i] = ft_strjoin(temp, cmd);
// 		free(temp);
// 		i++;
// 	}
// 	return (paths);
// }

// char	*get_cmd(char *str, char **envp)
// {
// 	char	*path;
// 	char	**paths;
// 	char	*full_cmd;
// 	int		i;

// 	if (str[0] == '/' || str[0] == '.')//more checks for this?
// 		return (str);
// 	i = 0;
// 	// path = get_env(envp);
// 	path = getenv("PATH=");
// 	if (!path)
// 		error_message("malloc error", 1);
// 	paths = get_path(path, str);
// 	if (!paths)
// 		error_message("malloc error", 1);
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
			return (free(path), free_arr(paths), NULL);
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
		if (access(full_cmd, F_OK) == TRUE)
			return (free_arr(paths), full_cmd);
		free(full_cmd);
		i++;
	}
	free_arr(paths);
	return (NULL);
}
