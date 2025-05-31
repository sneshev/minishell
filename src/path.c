/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:07:27 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/30 18:17:25 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char **envp)
{
	char	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env = envp[i] + 5;
			if (!env)
				perror("no env message\n");
			break ;
		}
		i++;
	}
	return (env);
}

char	**get_path(char *path, char *cmd)
{
	char	**paths;
	char	*temp;
	int		i;

	i = 0;
	paths = ft_split(path, ':');
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(temp, cmd);
		free(temp);
		i++;
	}
	return (paths);
}
