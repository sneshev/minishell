/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:07:27 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/04 16:36:12 by sneshev          ###   ########.fr       */
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
