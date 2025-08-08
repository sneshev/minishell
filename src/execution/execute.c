/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:39:33 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/26 13:13:51 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

void	handle_setup_close(t_list *list, int pip[3])
{
	if (list->prev)
		close(pip[2]);
	if (list->next)
	{
		pip[2] = pip[READ];
		close(pip[WRITE]);
	}
	if (!list->next && pip[2] != -1)
		close(pip[2]);
}

int	execute_list(t_list *list, int pid_count, t_env **env, char **environment)
{
	pid_t	pid[pid_count];
	int		pip[3];
	int		i;
	int		exitcode;

	i = 0;
	pip[2] = -1;
	while (i < pid_count)
	{
		if (list->next)
		{
			if (pipe(pip) == -1)
				perror_message("pipe");
		}
		pid[i] = fork();
		if (pid[i] == CHILD)
			child_process(list, pip, env, environment);
		handle_setup_close(list, pip);
		close_files(list);
		list = list->next;
		i++;
	}
	exitcode = wait_for_pids(pid, pid_count);
	return (exitcode);
}

int	execute(t_list *list, t_env **env)
{
	char	**environment;
	int		exitcode;

	disable_sigint();
	environment = convert_env(*env);
	if (!environment)
		return (-1);
	if (is_builtin(list->cmd) && !list->next)
	{
		exitcode = execute_builtin_parent(list, env, environment);
		return (free_arr(environment), exitcode);
	}
	exitcode = execute_list(list, count_pids(list), env, environment);
	return (free_arr(environment), exitcode);
}
