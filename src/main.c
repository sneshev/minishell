/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/08/08 11:36:55 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals/signals.h"
#include "history/history.h"
#include <readline/readline.h>
#include <readline/history.h>

char	*ft_readline(void)
{
	char	*line;

	if (isatty(STDIN_FILENO) == true)
	{
		line = readline("minishell$ ");
		ft_add_history(line, false);
	}
	else
		line = get_next_line(STDIN_FILENO);
	return (line);
}

// void	minishell(char *envp[])
void	minishell(char **envp)
{
	char	*line;
	t_list	*list;
	t_env	*env;
	int		exitcode;

	env = get_env(envp);
	ft_read_history();
	while (1)
	{
		enable_signals();
		line = ft_readline();
		if (!line)
		{
			write(1, "exit\n", 5);
			exit_with_code(0, NULL, &env, NULL);
		}
		list = get_list(line, env);
		free(line);
		if (list)
		{
			exitcode = execute(list, &env);
			free_list(&list);
			set_exit_code(exitcode);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (argc == 1)
		minishell(envp);
	return (0);
}
