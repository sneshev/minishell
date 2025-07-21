/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/21 21:27:34 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals/signals.h"
#include <readline/readline.h>
#include <readline/history.h>

void	minishell(char **envp)
{
	t_list	*list;
	t_env	*env;
	int		exitcode;

	list = NULL;
	env = NULL;
	env = get_env(envp);
	if (!env)
		return ;
	read_history(".minishell_history");
	while (1)
	{
		enable_signals();
		char	*line;
		line = readline("minishell$ ");

		if (!line || ft_strncmp(line, "exit", 4) == 0)
			exit_terminal(line);
		
		add_history(line);
		list = get_list(list, line, env);
		if (!list)
			printf("no list\n");
		else
		{
			exitcode = execute(list, &env);
			free_list(&list);
			set_exit_code(exitcode);
		}
		free(line);
		line = NULL;
	}
	free_env(&env);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	char *str[] = {
		"binkie=4\n", "puma=5\n", "yolo=6\n", "stefan=7\n", NULL};
	print_arr(str);
	minishell(str);
	return (0);
}
