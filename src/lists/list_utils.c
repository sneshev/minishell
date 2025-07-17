#include "../minishell.h"
#include "list.h"
#include <fcntl.h>

// if fd == -1 we will not pipe/close the pipe and the computer will read this as empty input

void	add_node_back(t_list **list, t_list *current)
{
	t_list	*temp;

	if (*list == NULL)
	{
		*list = current;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = current;
	current->prev = temp;
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

char	**get_cmd_args(char **tokens, int index)
{
	int		arg_count;
	char	**args;
	int		i;

	arg_count = count_cmd_args(tokens, index);
	if (arg_count < 1)
		return (NULL);
	args = xmalloc(sizeof(char *) * (arg_count + 1));
	i = 0;
	while (tokens[index] && !is_pipe(tokens[index]))
	{
		if (is_redirect(tokens[index]) && tokens[index + 1])
			index += 2;
		else
		{
			args[i] = ft_strdup(tokens[index]);
			if (!args[i])
				return (free_arr(args), NULL);
			i++;
			(index)++;
		}
	}
	args[i] = NULL;
	return (args);
}



