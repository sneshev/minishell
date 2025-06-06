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

void	execute_line(char *line)
{
	(void)line;
	printf("valid input\n");
}

// void	minishell(char *envp[])
void	minishell(char *line, char *envp[])
{
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
		if (is_valid_input(line, envp) == true)
			execute_line(line);
		// else
		// 	handle_invalid_input();
		break ;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	(void)argc;
	char *line = "wc -l -yuh -la wc";
	// if (argc != 1)
	// 	return (1);
	// enable_signals();
	minishell(line, envp);
	return (0);
}
