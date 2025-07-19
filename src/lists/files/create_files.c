#include "../../minishell.h"
#include "../../signals/signals.h"
#include "../list.h"
#include <errno.h>
#include <fcntl.h>

int fetch_infile(int fd[2], t_file *file)
{
	if (fd[0] > 0)
		close(fd[0]);
	if (file->type == REDIR_HEREDOC)
		return (handle_heredoc(file));
	fd[0] = (open(file->filename, O_RDONLY, 0400));
	if (fd[0] < 0)
	{
		printf("%s: ", file->filename);
    	if (errno == ENOENT)
    	    printf("No such file or directory\n");
		else if (errno == EACCES)
    	    printf("Permission denied\n");
		else
    	    printf("Open failed\n");
		return (-1);
	}
	return (fd[0]);
}

// no errors handled yet
int fetch_outfile(int fd[2], t_file *file)
{
	if (fd[1] > 0)
		close (fd[1]);
	if (file->type == REDIR_OUT)
		return (open(file->filename, O_TRUNC | O_WRONLY | O_CREAT, 0640));
	else if (file->type == REDIR_APPEND)
		return (open(file->filename, O_APPEND | O_WRONLY | O_CREAT, 0644));
	else
		return (-1);
}

// if its redirect i think we handle it by the flags in open function
int	create_files(int fd[2], t_file *file)
{
	fd[0] = -2;
	fd[1] = -2;
	while (file)
	{
		if (file->type == REDIR_IN || file->type == REDIR_HEREDOC)
			fd[0] = fetch_infile(fd, file);
		else if (file->type == REDIR_OUT || file->type == REDIR_APPEND)
			fd[1] = fetch_outfile(fd, file);
		if (fd[0] == -1 || fd[1] == -1)
			return (-1);
		file = file->next;
	}
	return (1);
}
