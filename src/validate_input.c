#include "minishell.h"

void handle_quotes(int arg_amount, char *args[])
{
	(void)args;
	(void)arg_amount;
}

char **get_args(char *line)
{
	char **args;
	int arg_amount;

	args = ft_split(line, ' ');
	if (!args)
		return (NULL);
	arg_amount = word_count(line);
	handle_quotes(arg_amount, args);
	return (args);
}

bool	is_valid_input(char *line, char **envp)
{
	t_node	*list;
	char	**args;
	int		wordc;

	args = get_args(line);
	if (!args)
		return (false);//should we specify its a malloc error?
	wordc = word_count(line);
	list = NULL;
	create_list(&list, args, wordc, envp);
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