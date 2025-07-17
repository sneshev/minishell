#include "../minishell.h"
#include "../signals/signals.h"
#include "list.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>


void heredoc_delim_msg(int line, char *delim)
{
	printf("warning: here-document at line ");
	printf("%d ", line);
	printf("delimited by end-of-file ");
	printf("(wanted `%s')\n", delim);
}

void child_heredoc(char *delim, int pipefd[2])
{
	char	*line;

	// enable_signals();
	close(pipefd[0]);

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			heredoc_delim_msg(-42, delim);
			free(line);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	exit(0);
}


int	handle_heredoc(t_file *file)
{
	int		pipefd[2];
	int		status;
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);

	pid = fork();
	if (pid == -1)
		return (-1);

	if (pid == 0)
		child_heredoc(file->filename, pipefd);
	else
	{
		disable_SIGINT();
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			close(pipefd[0]);
			return (-1);
		}
	}
	return (pipefd[0]);
}