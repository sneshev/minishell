/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:16:35 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/31 16:59:10 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_builtin(char *str)//some of these are also 2 (recognized by access) so what are they?
{
	// if (ft_strncmp(arg, "echo", 5) == 0) // ?	?	?
		// return (true);
	if (ft_strncmp(str, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(str, "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(str, "export", 7) == 0)
		return (true);
	if (ft_strncmp(str, "unset", 6) == 0)
		return (true);
	if (ft_strncmp(str, "env", 4) == 0)
		return (true);
	if (ft_strncmp(str, "exit", 5) == 0)
		return (true);
	return (false);
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
		return (perror("malloc error message\n"), false);
	while (paths[i])
	{
		full_cmd = ft_strdup(paths[i]);
		if (!full_cmd)
			return (free_array(paths), false);
		if (access(full_cmd, F_OK) == 0)
		{
			free_array(paths);
			free(full_cmd);
			return (true);
		}
		free(full_cmd);
		i++;
	}
	free_array(paths);
	return (false);
}


/*
	⬇️	this was the function before	⬇️
	
	return values did not match boolean and there was a leak
	if you tried to return full_cmd. But maybe the function 
	can be used to execute the commands too, thats why i did 
	not delete it but left it commented out
*/

// bool	is_command(char *str, char **envp)
// {
// 	char	*path;
// 	char	**paths;
// 	char	*full_cmd;
// 	int		i;

// 	if (str[0] == '/' || str[0] == '.')//more checks for this?
// 		return (str);
// 	i = 0;
// 	path = get_env(envp);
// 	paths = get_path(path, str);
// 	if (!paths)
// 		return (perror("malloc error message\n"), NULL);
// 	while (paths[i])
// 	{
// 		full_cmd = ft_strdup(paths[i]);
// 		if (!full_cmd)
// 			return (free_array(paths), NULL);
// 		if (access(full_cmd, F_OK) == 0)
// 			return (free_array(paths), full_cmd);
// 		free(full_cmd);
// 		i++;
// 	}
// 	free_array(paths);
// 	return (NULL);
// }


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
bool	is_flag(char *str)
{
	(void)str;
	return false;
}

// return (-2); for unclosed brackets
// doenst handle a string with spaces in between
// example: "hello my name is"
int is_quote(char *str)
{
	int last_chr;

	if (!str)
		return (0);
	if (*str == '\'')
	{
		last_chr = ft_strlen(str) - 1;
		if (str[last_chr] == '\'' && last_chr)
			return (SQUOTE);
		else
			return (-2);
	}
	else if (*str == '\"')
	{
		last_chr = ft_strlen(str) - 1;
		if (str[last_chr] == '\"' && last_chr)
			return (DQUOTE);
		else
			return (-2);
	}
	else
		return (0);
}

int	find_arg_type(char *arg, char **envp)
{
	if (is_builtin(arg))
		return (BUILTIN);
	if (is_command(arg, envp))
		return (COMMAND);
	if (is_flag(arg))
		return (FLAG);
	if (is_pipe(arg))
		return (PIPE);
	if (is_redirect(arg))
		return (REDIRECTION);
	if (is_quote(arg))
		return (is_quote(arg));
	return (-1);
}