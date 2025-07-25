/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/25 15:25:15 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals/signals.h"
#include <readline/readline.h>
#include <readline/history.h>

// void	minishell(char *envp[])
void	minishell(char **envp)
{
	char	*line;
	t_list	*list;
	t_env	*env;

	list = NULL;
	env = get_env(envp);
	if (!env)
		return ;
	// ft_read_history(".minishell_history");
	while (1)
	{
		enable_signals();
		line = readline("minishell$ ");
		if (!line)
			exit_by_signal();
		ft_add_history(line);
		list = get_list(list, line, env);
		if (list)
			set_exit_code(execute(list, &env));
	}
	free_g_env();
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
