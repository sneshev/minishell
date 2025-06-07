/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/04 16:31:55 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	minishell(char *envp[])
void	minishell(char *line, char **envp)
{
	t_list	*list;

	list = NULL;
	while (1)
	{
		// char *line = readline("minishell$ ");
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
		execute(&list);
		// else
		// 	handle_invalid_input();
		break ;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (argc != 1)
		return (1);
	// enable_signals();
	minishell(argv[1], envp);
	return (0);
}
