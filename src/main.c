/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/05 12:55:50 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals/signals.h"
#include <readline/readline.h>
#include <readline/history.h>

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
	read_history(".minishell_history");
	while (1)
	{
		char	*line;
		line = readline("minishell$ ");
		// line = "cat < info.txt > outfile1 | cat err.log < infile2 > outfile2 ";

		if (!line || ft_strncmp(line, "exit", 4) == 0)
			exit_terminal(line);
		
		list = get_list(list, line, get_env(envp));
		if (!list)
			printf("no list\n");
		
		add_history(line);
		// print_list(list);
		execute(list, envp, count_pids(list));
		free_list(&list);
	}

}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;

	minishell(envp);
	return (0);
}
