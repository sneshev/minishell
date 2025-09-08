/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:16:35 by mmisumi           #+#    #+#             */
/*   Updated: 2025/09/08 13:30:26 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_quote(char c)
{
	if (c == '\'')
		return (true);
	else if (c == '\"')
		return (true);
	else
		return (false);
}

bool	is_heredoc(char *str)
{
	if (!str || !*str)
		return (false);
	if (*str == '<')
	{
		str++;
		if (*str == '<')
			return (true);
	}
	return (false);
}

bool	is_redirect(char *str)
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
	if (!str || !(*str))
		return (false);
	if (*str == '|' && *(str + 1) == '\0')
		return (true);
	return (false);
}

bool	is_directory(const char *path)
{
	struct stat	st;

	if (!path)
		return (false);
	if (stat(path, &st) == 0)
		return (S_ISDIR(st.st_mode));
	return (false);
}
