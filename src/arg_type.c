/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:16:35 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/31 16:14:10 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (free_array(paths), NULL);
		if (access(full_cmd, F_OK) == 0)
			return (free_array(paths), full_cmd);
		free(full_cmd);
		i++;
	}
	free_array(paths);
	return (NULL);
}

bool is_redirect(char *str)
{
	if (!(*str))
		return (false);
	if (*str == '<')
	{
		str++;
		if (*str == '\0')
			return (true);
		if (*str == '<' && (*(str + 1) == '\0'))
			return (true);
	}	
	else if (*str == '>')
	{
		str++;
		if (*str == '\0')
			return (true);
		if (*str == '>' && (*(str + 1) == '\0'))
			return (true);
	}
	return (false);
}

bool	is_pipe(char *str)
{
	if (*str == '|' && *(str + 1) == '\0')
		return (true);
	return (false);
}

//for now im only taking care of -, well see later if -- is needed too
bool	is_flag()
{
	return false;
}