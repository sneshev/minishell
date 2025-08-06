/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:42:16 by sneshev           #+#    #+#             */
/*   Updated: 2025/07/26 15:42:44 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "history.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

static bool	is_empty_string(char *line)
{
	while (line && *line)
	{
		if (!is_space(*line))
			return (false);
		line++;
	}
	return (true);
}

int	ft_read_history(void)
{
	int		fd;
	char	*line;
	char	*cpy;

	fd = open(".minishell_history", O_RDONLY | O_CREAT, 0640);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		cpy = ft_strdup(line);
		if (cpy)
			add_history(cpy);
		free(cpy);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	ft_add_history(char *line)
{
	int	fd;
	

	if (is_empty_string(line))
		return (-1);
	add_history(line);
	// getcwd();
	fd = open(".minishell_history", O_WRONLY | O_CREAT | O_APPEND, 0640);
	if (fd < 0)
		return (-1);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	close(fd);
	return (1);
}
