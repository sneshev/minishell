#include "../../minishell.h"
#include "../../signals/signals.h"
#include "../list.h"
#include <fcntl.h>

void	create_files(int fd[2], t_file *file)
{
	int		infile;
	int		outfile;

	// -2 for not set up yet
	infile = -2;
	outfile = -2;
	while (file)
	{
		if (file->type == REDIR_IN)
		{
			if (infile > 0)
				close(infile);
			infile = open(file->filename, O_RDONLY, 0400);
		}
		else if (file->type == REDIR_HEREDOC)
		{
			if (infile > 0)
				close(infile);
			infile = handle_heredoc(file);
		}
		else if (file->type == REDIR_OUT)
		{
			if (outfile > 0)
				close (outfile);
			outfile = open(file->filename, O_TRUNC | O_WRONLY | O_CREAT, 0640);
		}
		else if (file->type == REDIR_APPEND)
		{
			if (outfile > 0)
				close(outfile);
			outfile = open(file->filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
		}
		if (infile == -1 || outfile == -1)
		{
			perror_message(file->filename);
			fd[0] = -1;
			fd[1] = -1;
			return ;
		}
		file = file->next;
	}
	fd[0] = infile;
	fd[1] = outfile;
}
