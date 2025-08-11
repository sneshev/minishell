/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:44:46 by sneshev           #+#    #+#             */
/*   Updated: 2025/08/11 21:02:22 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../signals/signals.h"
#include "../../tokens/tokens.h"
#include "../list.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>

bool	has_quote(char *str)
{
	while (str && *str)
	{
		if (is_quote(*str))
			return (true);
		str++;
	}
	return (false);
}

char	*delim_alloc(char *str)
{
	char	quote_type;
	int		len;

	len = 0;
	while (*str)
	{
		if (is_quote(*str))
		{
			quote_type = *str;
			while (*++str != quote_type)
				len++;
			str++;
		}
		else
		{
			len++;
			str++;
		}
	}
	return ((char *)malloc(len * sizeof(char) + 1));
}

size_t	add_heredoc_quoted_seq(
		char *delim, char *str, size_t len, char quote_type)
{
	quote_type = *str;
	while (*++str && *str != quote_type)
	{
		delim[len] = *str;
		len++;
	}
	return (len);
}

char	*find_delim(char *str)
{
	char	*delim;
	size_t	quote_len;
	size_t	i;

	if (!str)
		return (NULL);
	if (!*str)
		return (strdup(""));
	delim = delim_alloc(str);
	if (!delim)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (is_quote(*str))
		{
			quote_len = add_heredoc_quoted_seq(delim + i, str, 0, 0);
			str += quote_len + 2;
			i += quote_len;
		}
		else
			delim[i++] = *(str++);
	}
	delim[i] = '\0';
	return (delim);
}
