#include "../../minishell.h"
#include "../../signals/signals.h"
#include "../list.h"
#include <errno.h>
#include <fcntl.h>

int fetch_infile(int infile, t_file *file)
{
	if (infile > 0)
		close(infile);
	if (file->type == REDIR_HEREDOC)
		return (handle_heredoc(file));
	infile = open(file->filename, O_RDONLY, 0400);
	if (infile < 0)
	{
    	if (errno == ENOENT)
    	    write_err(file->filename, "No such file or directory\n");
		else if (errno == EACCES)
    	    write_err(file->filename, "Permission denied\n");
		else
    	    write_err(file->filename, "Open failed\n");
	}
	return (infile);
}

// no errors handled yet
int fetch_outfile(int outfile, t_file *file)
{
	if (outfile > 0)
		close (outfile);
	if (file->type == REDIR_OUT)
		outfile = open(file->filename, O_TRUNC | O_WRONLY | O_CREAT, 0640);
	else if (file->type == REDIR_APPEND)
		outfile = open(file->filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (outfile < 0)
	{
		if (errno == EACCES)
    	    write_err(file->filename, "Permission denied\n");
		else
    	    write_err(file->filename, "Open failed\n");
	}
	return (outfile);

}

// if its redirect i think we handle it by the flags in open function
int	create_files(int fd[2], t_file *file)
{
	int infile;
	int outfile;

	infile = -2;
	outfile = -2;
	while (file)
	{
		if (file->type == REDIR_OUT || file->type == REDIR_APPEND)
			outfile = fetch_outfile(outfile, file);
		else if (file->type == REDIR_IN || file->type == REDIR_HEREDOC)
			infile = fetch_infile(infile, file);
		if (infile == HEREDOC_TERMINATED)
			return (HEREDOC_TERMINATED);
		if (infile == -1 || outfile == -1)
		{
			fd[0] = -1;
			fd[1] = -1;
			return (-1);
		}
		file = file->next;
	}
	fd[0] = infile;
	fd[1] = outfile;
	return (1);
}
