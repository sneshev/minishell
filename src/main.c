/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/02 12:02:50 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_line(char *line)
{
	(void)line;
}

void	minishell(char *envp[])
{
	while (1)
	{
		char *line = readline("minishell$ ");
		if (!line || ft_strncmp(line, "exit", 5) == 0)
		{
			write(1, "exit\n", 5);
			exit(1);
		}
		if (g_signal == SIGINT)
			receive_SIGINT();
		if (is_valid_input(line, envp) == true)
			execute_line(line);
		else
			handle_invalid_input();
	}
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (argc != 1)
		return (1);
	enable_signals();
	minishell(envp);
	return (0);
}
