#include "../minishell.h"
#include "../signals/signals.h"
#include "list.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

int	handle_heredoc(t_file *file)
{
	int pipefd[2];
	char *line;
	char *delim;

	delim = file->filename;
	if (pipe(pipefd) == -1)
	{
		// error
		return (-1);
	}
	line = readline("> ");
	while (line)
	{
		if (strcmp(line, delim) == 0)
		{
			free(line);
			line = NULL;
		}
		else
		{
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
			line = readline("> ");
		}
	}
	close (pipefd[1]);
	return (pipefd[0]);
}