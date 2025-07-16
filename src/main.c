/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/16 19:36:01 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals/signals.h"
#include <readline/readline.h>
#include <readline/history.h>

// void	minishell(char *envp[])
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
		char	*line;
		line = readline("minishell$ ");
		// line = "^C";

		if (!line || ft_strncmp(line, "exit", 4) == 0)
			exit_terminal(line);
		
		add_history(line);
		list = get_list(list, line, env);
		// print_list(list);
		if (!list)
			printf("no list\n");
		else
		{
			exitcode = execute(list, &env);
			free_list(&list);
			env->value = ft_itoa(exitcode);
			if (!env->value)
				return (free_env(&env));
		}
		free(line);
		line = NULL;
	}
	free_env(&env);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)envp;
	(void)argc;
	(void)argv;
	// char *yo[] = {
	// 	"hello=hihihi\n",
	// 	"goodmorning=sunsunsun\n",
	// 	"binkie=cutecutecute\n",
	// 	NULL};
	// enable_signals();
	minishell(envp);
	return (0);
}
