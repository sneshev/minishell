#include "minishell.h"

// we will validate the syntax with pipes and redirections, later after we have the list we will open outfiles
// if we have invalid file we stop the process and move on until after the pipe, thus no pipe is created (by updating the list)
bool    validate_syntax(char **tokens)
{
    int i;

    i = 0;
	if (is_pipe(tokens[i]))
		return (false);
	while (tokens[i])
	{
		if (is_pipe(tokens[i]) && is_pipe(tokens[i + 1]))
			return (false);
		if (is_redirect(tokens[i]) && is_redirect(tokens[i + 1]))
			return (false);
		// im not sure if were supposed to take care of uncomplete commands
		if (tokens[i + 1] == NULL)
		{
			if (is_pipe(tokens[i]) || is_redirect(tokens[i]))
				return (false);
		}
		i++;
	}
	return (true);
}

// bool	validate_files(char **tokens, char **envp)
// {
	
// }

// void	validation(char *s)
// {
// 	char	**tokens = NULL;
// 	t_list	*list = NULL;

// 	tokens = get_tokens(s);
// 	if (!tokens)
// 		error_message("malloc error", 1);
// 	if (!validate_syntax(tokens))
// 		error_message("invalid syntax", 1);
// 	create_list(&list, tokens, count_tokens(s), envp);
// 	print_list(list);
// 	validate_files();



// int main(int argc, char *argv[], char *envp[])
// {
// 	// (void)argc;
// 	// (void)argv;
// 	if (argc != 2)
// 		return (1);
// 	// char *s = "cat | > outfile cat < infile | cat";
// 	char **tokens = get_tokens(argv[1]);
// 	if (!tokens)
// 		return (0);
// 	if (validate_syntax(tokens))
// 		printf("true\n");
// 	else
// 		printf("false\n");
// 	t_list	*list = NULL;
// 	create_list(&list, tokens, count_tokens(argv[1]), envp);
// 	print_list(list);
// 	validate_files(&list);
// 	return (0);
// }