#include "../../minishell.h"
#include "../../signals/signals.h"
#include "../list.h"
#include <fcntl.h>

// if fd == -1 we will not pipe/close the pipe and the computer will read this as empty input

char	**get_redir_files(char **tokens, int index, int file_count)
{
	char	**files;
	int		i;

	files = xmalloc(sizeof(char *) * (file_count + 1));
	// printf("file malloc: %d\n", count_redir_files(tokens, index));
	i = 0;
	while (tokens[index] && !is_pipe(tokens[index]))
	{
		if (is_redirect(tokens[index]) && tokens[index + 1])
		{
			files[i] = ft_strdup(tokens[index]);
			if (!files[i])
				return (free_arr(files), NULL);
			// printf("files[%d]: %s\n", i, files[i]);
			files[i + 1] = ft_strdup(tokens[index + 1]);
			if (!files[i + 1])
				return (free_arr(files), NULL);
			// printf("files[%d]: %s\n", i + 1, files[i + 1]);
			i += 2;
			index += 2;
		}
		else
			index++;
	}
	files[i] = NULL;
	// printf("files[%d]: %s\n", i, files[i]);
	return (files);
}

t_file	*get_file_list(t_file *file, char **tokens, int index, int file_count)
{
	char	**files;

	files = get_redir_files(tokens, index, file_count);
	if (!files)
		return (NULL);
	// print_arr(files);
	file = create_file_list(file, files);
	if (!file)
		return (free_arr(files), NULL);
	return (file);
}

t_file	*create_file_list(t_file *file, char **files)
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
