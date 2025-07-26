/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:37:21 by sneshev           #+#    #+#             */
/*   Updated: 2025/07/26 14:43:17 by sneshev          ###   ########.fr       */
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

char	*find_delim(char *str);

void	child_heredoc(char *delim, bool quoted, int pipefd[2], t_env *env)
{
	char	*line;

	close(pipefd[0]);
	while (1)
	{
		line = heredoc_readline(quoted, env);
		if (!line || !ft_strcmp(line, delim))
			end_heredoc(&line, delim, pipefd);
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
}

int	parent_heredoc(pid_t pid, int pipefd[2])
{
	int		status;

	disable_sigint();
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		close(pipefd[0]);
		return (0);
	}
	return (1);
}

int	handle_heredoc(t_file *file, t_env *env)
{
	int		pipefd[2];
	char	*delim;
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	delim = NULL;
	if (pid == 0)
	{
		reset_sigint();
		delim = find_delim(file->filename);
		if (!delim && find_quote_len(file->filename, NULL, 0, 0) < 0)
			return (printf("unclosed quotes"), kill(0, SIGINT), -7);
		child_heredoc(delim, has_quote(file->filename), pipefd, env);
	}
	if (!parent_heredoc(pid, pipefd))
		pipefd[0] = -7;
	if (delim)
		free(delim);
	return (pipefd[0]);
}
