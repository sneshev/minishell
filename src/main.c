/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/26 17:40:52 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals/signals.h"
#include "history/history.h"
#include <readline/readline.h>
#include <readline/history.h>

void end_of_cycle(char **line, t_list **list)
{
	free(*line);
	*line = NULL;
	free_list(list);
	*list = NULL;
}

char *ft_readline()
{
	char *line;

	if (isatty(STDIN_FILENO) == true)
	{
		line = readline("minishell$ ");
		ft_add_history(line);
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
	if (!env)
		return ;
	// ft_read_history(".minishell_history");
	while (1)
	{
		enable_signals();
		line = ft_readline();
		if (!line)
			exit_with_code(0);
		list = get_list(line, env);
		if (list)
		{
			exitcode = execute(list, &env);
			set_exit_code(exitcode);
		}
		end_of_cycle(&line, &list);
	}
	free_env(&env);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (argc == 1)
		minishell(envp);
	return (0);
}
