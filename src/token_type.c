/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:16:35 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/21 12:25:29 by mmisumi          ###   ########.fr       */
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

bool	is_command(char *str)
{
	char	*cmd;

	cmd = get_cmd(str);
	if (!cmd)
		return (false);
	free(cmd);
	return (true);
}

bool is_redirect(char *str)
{
	if (!str || !(*str))
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
	if (!str)
		return (false);
	if (*str == '|' && *(str + 1) == '\0')
		return (true);
	return (false);
}

int	find_token_type(char *arg)
{
	if (is_builtin(arg))
		return (BUILTIN);
	if (is_command(arg))
		return (COMMAND);
	if (is_pipe(arg))
		return (PIPE);
	if (is_redirect(arg))
		return (REDIRECTION);
	return (UNDEFINED);
}
