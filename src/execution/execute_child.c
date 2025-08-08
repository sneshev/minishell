/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:02:47 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/25 12:51:40 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

void	setup_input(t_list *list, int pip[3])
{
	if (list->next)
		close(pip[READ]);
	if (list->input == -2)
	{
		if (list->prev)
		{
			dup2(pip[2], STDIN_FILENO);
			close(pip[2]);
		}
	}
	else if (list->input >= 0)
	{
		if (list->prev)
			close(pip[2]);
		dup2(list->input, STDIN_FILENO);
		close(list->input);
	}
}

void	setup_output(t_list *list, int *pip)
{
	if (list->output == -2)
	{
		if (list->next)
		{
			dup2(pip[WRITE], STDOUT_FILENO);
			close(pip[WRITE]);
		}
	}
	else if (list->output >= 0)
	{
		dup2(list->output, STDOUT_FILENO);
		close(list->output);
		if (list->next)
			close(pip[WRITE]);
	}
}

void	handle_fd_closing(t_list *list, int pip[3])
{
	if (list->next)
	{
		close(pip[READ]);
		close(pip[WRITE]);
	}
	if (list->prev)
		close(pip[2]);
	close_files(list);
}

void	child_process(t_list *list, int pip[3], t_env **env, char **environment)
{
	int	exitcode;

	reset_signals();
	if (!list->args)
	{
		handle_fd_closing(list, pip);
		exit (0);
	}
	exitcode = check_invalid_file_cmd(list, *env);
	if (exitcode != 0)
	{
		handle_fd_closing(list, pip);
		exit(exitcode);
	}
	setup_input(list, pip);
	setup_output(list, pip);
	if (is_builtin(list->cmd))
	{
		exitcode = execute_builtin(list, env, environment);
		exit (exitcode);
	}
	else
		execve(list->cmd, list->args, environment);
}
