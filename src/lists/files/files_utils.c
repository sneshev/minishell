#include "../../minishell.h"
#include "../list.h"
#include <fcntl.h>

int	count_redir_files(char **tokens, int index)
{
	int	count;

	count = 0;
	while (tokens[index] && !is_pipe(tokens[index]))
	{
		if (is_redirect(tokens[index]) && tokens[index + 1])
		{
			count += 2;
			index += 2;
		}
		else
			index++;
	}
	return (count);
}

t_redir_type find_redir_type(char *str)
{
	if (*str == '<')
	{
		str++;
		if (*str != '<')
			return (REDIR_IN);
		else
			return (REDIR_HEREDOC);
	}
	else
	{
		str++;
		if (*str != '>')
			return (REDIR_OUT);
		else
			return (REDIR_APPEND);
	}
}

t_file	*new_file_node(char *redir_type, char *filename)
{
	t_file	*node;

	node = xmalloc(sizeof(t_file));
	node->type = find_redir_type(redir_type);
	node->filename = ft_strdup(filename);
	if (!node->filename)
		return (NULL);
	node->next = NULL;
	return (node);
}

void	add_filenode_back(t_file **file, t_file *current)
{
	t_file	*temp;

	if (*file == NULL)
	{
		*file = current;
		return ;
	}
	temp = *file;
	while (temp->next)
		temp = temp->next;
	temp->next = current;
}

