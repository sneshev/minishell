/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:12:53 by sneshev           #+#    #+#             */
/*   Updated: 2025/09/08 13:32:24 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include <stddef.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	char		*red;
	char		*line;
	static char	*saved;
	int			bytes_red;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	red = NULL;
	while (1)
	{
		if (saved == NULL)
			bytes_red = use_read(fd, &red);
		else
			bytes_red = use_saved(&line, &saved);
		if (bytes_red > 0)
		{
			if (red)
				line = add_to_line(&line, &red);
			if ((bytes_red < BUFFER_SIZE && red != NULL) || find_nl(line) != -1)
				return (ret(line, &red, &saved, bytes_red));
		}
		else
			return (ret(line, &red, &saved, bytes_red));
	}
}

char	*add_to_line(char **line_ptr, char **red_ptr)
{
	char	*temp;
	char	*line;
	char	*red;

	red = *red_ptr;
	line = *line_ptr;
	temp = ft_strjoin(line, red);
	free(line);
	free(red);
	return (temp);
}

int	use_read(int fd, char **red)
{
	int	bytes_red;

	*red = malloc(BUFFER_SIZE + 1);
	if (!(*red))
		return (-1);
	bytes_red = read(fd, *red, BUFFER_SIZE);
	if (bytes_red <= 0)
	{
		free(*red);
		*red = NULL;
	}
	else
		(*red)[bytes_red] = '\0';
	return (bytes_red);
}

int	use_saved(char **line, char **saved)
{
	if (ft_strlen(*saved) > 0)
		*line = ft_strdup(*saved);
	free (*saved);
	*saved = NULL;
	if (ft_strlen(*line) == 0)
		return (1);
	return (ft_strlen(*line));
}

char	*ret(char *line, char **red, char **saved, int bytes_red)
{
	char	*nline;
	int		nlen;

	if (bytes_red == -1)
		return (free(line), free(*saved), NULL);
	if (*red == NULL && line != NULL && find_nl(line) == -1)
		return (line);
	if (bytes_red == 0)
		return (free(line), free(*saved), free(*red), NULL);
	else if (((bytes_red < BUFFER_SIZE) && find_nl(line) == -1))
		return (line);
	else
	{
		nlen = find_nl(line);
		nline = ft_substr(line, 0, find_nl(line) - 1);
		*saved = ft_substr(line, nlen, ft_strlen(line) - nlen);
		return (free (line), nline);
	}
}
