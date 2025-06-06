#include "minishell.h"

// bool	check_arg_order(t_node **list)
// {
// 	(void)list;
// 	return (true);
// }

bool	is_valid_input(char *line, char **envp)
{
	t_list	*list;
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
	// check_arg_order(&line);
	print_list(list);
	print_line(list);
	execute(&list);
	free_list(&list);
	return (true);
}

// void	handle_invalid_input(void)
// {
// 	if ()
// }