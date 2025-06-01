#include "minishell.h"


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
	print_list(list);
	free_list(&list);
	return (true);
}

void	handle_invalid_input(void)
{

}