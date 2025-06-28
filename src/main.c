/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/28 15:27:54 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// void	minishell(char *envp[])
void	minishell(char **envp)
{
	t_list	*list;

	list = NULL;
	// while (1)
	{
		char	*line;
		// line = readline("minishell$ ");
		line = "cat < info.txt > outfile1 | cat err.log < infile2 > outfile2 ";
		if (!line || ft_strncmp(line, "exit", 5) == 0)
		{
			write(1, "exit\n", 5);
			exit(1);
		}
		// if (g_signal == SIGINT)
		// 	receive_SIGINT();

		list = get_list(list, line, envp);
		if (!list)
			error_message("no list", -1);
		print_list(list);
		// execute(list);
		// else
		// 	handle_invalid_input();
		// break ;
	}
}

// int main(int argc, char *argv[], char *envp[])
// {
// 	(void)argc;
// 	(void)argv;
// 	// char *line = "ls -la";
// 	// if (argc != 1)
// 	// 	return (1);
// 	// enable_signals();
// 	minishell(envp);
// 	return (0);
// }
