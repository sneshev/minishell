/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:45:40 by sneshev           #+#    #+#             */
/*   Updated: 2025/08/11 20:59:37 by stefuntu         ###   ########.fr       */
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

int	find_envvar_len(char *str, t_env *env);

static size_t	find_len(char *line, t_env *env, size_t len)
{
	while (*line)
	{
		if (*line == '$')
		{
			line++;
			len += find_envvar_len(line, env);
			line += find_varname_len(line);
		}
		else
		{
			len++;
			line++;
		}
	}
	return (len);
}

static char	*expand_line(char **line, t_env *env, size_t len)
{
	char	*line2;
	size_t	i;
	size_t	j;

	if (len == 0)
		return (ft_strdup(""));
	line2 = (char *)malloc(len * sizeof(char) + 1);
	if (!line2)
		return (free(*line), exit(1), NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if ((*line)[j] == '$')
		{
			j += 1;
			add_env_variable(line2, *line + j, (int *)&i, env);
			j += find_varname_len(*line + j);
		}
		else
			line2[i++] = (*line)[j++];
	}
	line2[i] = '\0';
	free(*line);
	return (line2);
}

char	*heredoc_readline(bool quoted, t_env *env)
{
	char	*line;

	line = readline("> ");
	if (line && !quoted)
		return (expand_line(&line, env, find_len(line, env, 0)));
	else
		return (line);
}

void	end_heredoc(char **line, char *delim, int pipefd[2])
{
	if (*line)
		free(*line);
	else
	{
		printf("warning: here-document at line ? ");
		printf("delimited by end-of-file ");
		printf("(wanted `%s')\n", delim);
	}
	close(pipefd[1]);
	exit(0);
}
