/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:07:27 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/30 18:08:54 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_count(char const *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0')
		{
			j++;
			while (s[i] != ' ' && s[i] != '\0')
				i++;
		}
	}
	return (j);
}

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

bool	is_command(char *str, char **envp)
{
	char	*path;
	char	**paths;
	char	*full_cmd;
	int		i;

	if (str[0] == '/' || str[0] == '.')//more checks for this?
		return (str);
	i = 0;
	path = get_env(envp);
	paths = get_path(path, str);
	if (!paths)
		return (perror("malloc error message\n"), NULL);
	while (paths[i])
	{
		full_cmd = ft_strdup(paths[i]);
		if (!full_cmd)
			return (free_path(paths[i]), NULL);
		if (access(full_cmd, F_OK) == 0)
			return (free_path(paths, i), full_cmd);//have to double check how the i works in freeing the paths
		free(full_cmd);
		i++;
	}
	free_path(paths, i);
	return (NULL);
}
