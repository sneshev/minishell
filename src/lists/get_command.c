/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:07:27 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/21 17:36:32 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	check_access(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, F_OK) == -1)
		{
			write_err(cmd, "No such file or directory\n");
			return ;
		}
	}
	else
	{
		if (access(cmd, F_OK) == -1)
		{
			write_err(cmd, "command not found\n");
			return ;
		}
	}
	if (access(cmd, X_OK) == -1)
	{
		write_err(cmd, "Permission denied\n");
		return ;
	}
}

char	*check_executable(char *cmd)
{
	char	*full_cmd;

	full_cmd = ft_strdup(cmd);
	if (!full_cmd)
		return (NULL);
	if (access(full_cmd, F_OK) == 0)
		return (full_cmd);
	write_err(cmd, "No such file or direcory\n");
	return (NULL);
}

char	*get_cmd(char *cmd)
{
	char	**paths;
	char	*full_cmd;
	int		i;

	if (cmd[0] == '/' || cmd[0] == '.')
		return (check_executable(cmd));
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
	write_err(cmd, "command not found\n");
	free_arr(paths);
	return (NULL);
}
