#include "minishell.h"

int	flag_count(t_node **list)
{
	t_node	*temp;
	int		flagc;

	temp = *list;
	while (temp)
	{
		if (temp->arg == UNDEFINED)
		{
			flagc++;
			temp = temp->next;
		}
		else
			break ;
	}
	return (flagc);
}

bool	get_flags(t_node **list)
{
	t_node	*temp;
	char	**flags;
	int		flagc;
	int		i;

	flagc = flag_count(list);
	flags = malloc(sizeof(char *) * (flagc + 1));
	if (!flags)
		return (false);
	i = 0;
	while (i <= flagc)
	{
		if (i == 0)
			flags[i] = temp->prev->arg;
		else
			flags[i] = temp->arg;
		i++;
	}
	return (*flags);
}

bool	check_arg_order(t_node **list)
{
	(void)list;
	return (true);
}

bool	is_valid_input(char *line, char **envp)
{
	t_node	*list;
	char	**args;
	int		arg_count;

	args = get_args(line);
	if (!args)
		return (free_arr(args), false);
	arg_count = count_args(line);
	list = NULL;
	create_list(&list, args, arg_count, envp);
	free_arr(args);
	if (!list)
		return (false);
	check_arg_order(&line);
	print_list(list);
	free_list(&list);
	return (true);
}

void	handle_invalid_input(void)
{
	if ()
}