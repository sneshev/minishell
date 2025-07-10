/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/05 15:46:30 by mmisumi          ###   ########.fr       */
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
		// line = "unset mitani";

		if (!line || ft_strncmp(line, "exit", 4) == 0)
			exit_terminal(line);
		
		list = get_list(list, line, env);
		if (!list)
			continue ;			
		add_history(line);
		print_list(list);
		exitcode = execute(list, &env, count_pids(list));
		free_list(&list);
	}
	printf("exitcode: %d\n", exitcode);
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

	minishell(envp);
	return (0);
}
