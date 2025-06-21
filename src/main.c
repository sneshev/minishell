/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/21 11:52:43 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	minishell(char *envp[])
void	minishell(char **envp)
{
	t_list	*list;

	list = NULL;
	// while (1)
	{
		char	*line;
		// line = readline("minishell$ ");
		line = "cat info.txt ";
		if (!line || ft_strncmp(line, "exit", 5) == 0)
		{
			write(1, "exit\n", 5);
			exit(1);
		}
		// if (g_signal == SIGINT)
		// 	receive_SIGINT();

		list = get_list(line, envp);
		if (!list)
			error_message("malloc error", 1);
		print_line(list);
		
		// execute(&list);
		// else
		// 	handle_invalid_input();
		// break ;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	// char *line = "ls -la";
	// if (argc != 1)
	// 	return (1);
	// enable_signals();
	minishell(envp);
	return (0);
}
