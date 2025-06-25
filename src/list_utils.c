#include "minishell.h"

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

int		count_cmd_args(char **tokens, int index)
{
	int	count;

	count = 0;
	while(tokens[index] && !is_pipe(tokens[index]))
	{
		if (is_redirect(tokens[index]) && tokens[index + 1])
			index += 2;
		else
		{
			count++;
			index++;
		}
	}
	return (count);
}

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

char	**get_cmd_args(char **tokens, int *index)
{
	int		arg_count;
	char	**args;
	int		i;

	arg_count = count_cmd_args(tokens, *index);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens[*index] && !is_pipe(tokens[*index]))
	{
		if (is_redirect(tokens[*index]) && tokens[*index + 1])
			*index += 2;
		else
		{
			args[i] = ft_strdup(tokens[*index]);
			if (!args[i])
				return (free_arr(args), NULL);
			i++;
			(*index)++;
		}
	}
	printf("index before pipe: %d\n", *index);
	(*index)++;
	args[i] = NULL;
	return (args);
}

char	**get_redir_files(char **tokens, int index)
{
	char	**files;
	int		i;

	files = malloc(sizeof(char *) * (count_redir_files(tokens, index) + 1));
	if (!files)
		return (NULL);
	i = 0;
	while (tokens[index] && !is_pipe(tokens[index]))
	{
		if (is_redirect(tokens[index]) && tokens[index + 1])
		{
			files[i] = ft_strdup(tokens[index]);
			if (!files[i])
				return (free_arr(files), NULL);
			files[i + 1] = ft_strdup(tokens[index + 1]);
			if (!files[i + 1])
				return (free_arr(files), NULL);
			i += 2;
			index += 2;
		}
		else
			index++;
	}
	files[i] = NULL;
	return (files);
}

t_file	*new_file_node(char *redir_type, char *filename)
{
	t_file	*node;

	node = malloc(sizeof(t_file));
	if (!node)
		return (NULL);
	node->type = find_redir_type(redir_type);
	node->filename = ft_strdup(filename);
	if (!node->filename)
		return (NULL);
	node->next = NULL;
	return (node);
}

t_file	*put_redir_files(t_file *file, char **files)
{
	t_file	*new;
	int		i;

	i = 0;
	while (files[i] && files[i + 1])
	{
		new = new_file_node(files[i], files[i + 1]);
		if (!new)
			return (free_file(&file), NULL);
		add_filenode_back(&file, new);
		i += 2;
	}
	return (file);
}

int	handle_heredoc(t_file **file)
{
	(void)file;
	printf("heredoc\n");
	return (0);
}

int	create_files(int fd[2], t_file *file)
{
	int		infile;
	int		outfile;

	while (file)
	{
		if (file->type == REDIR_IN)
			infile = open(file->filename, O_RDONLY, 0400);
		else if (file->type == REDIR_HEREDOC)
			handle_heredoc(&file);
		else if (file->type == REDIR_OUT)
			outfile = open(file->filename, O_TRUNC | O_WRONLY | O_CREAT, 0640);
		else if (file->type == REDIR_APPEND)
			outfile = open(file->filename, O_WRONLY | O_CREAT, 0644);
		if (outfile == -1 || infile == -1)
			return(1);
		file = file->next;
	}
	fd[0] = infile;
	fd[1] = outfile;
	return (0);
}
