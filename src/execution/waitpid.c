/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:18:02 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/24 15:18:42 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

int	count_pids(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		list = list->next;
		count++;
	}
	return (count);
}

int	wait_for_pids(pid_t *pid, int pid_count)
{
	int	i;
	int	status;
	int	exitcode;

	i = 0;
	status = 0;
	exitcode = 0;
	while (i < pid_count - 1)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WEXITSTATUS(status))
		exitcode = (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
		else if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
	return (exitcode);
}
