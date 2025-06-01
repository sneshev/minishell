/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/31 16:42:28 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char *line)
{
	(void)line;
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (argc != 1)
		return (1);
	enable_signals();
	while(1)
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
			minishell(line);
		else
			handle_invalid_input();
	}
	return (0);
}
