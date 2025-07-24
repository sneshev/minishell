/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:02:47 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/24 14:03:50 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

void	setup_input(t_list *list, int *pip, int prev_pipe)
{
	if (list->next)
		close(pip[READ]);
	if (list->input == -2)
	{
		if (list->prev)
		{
			dup2(prev_pipe, STDIN_FILENO);
			close(prev_pipe);
		}
	}
	else if (list->input >= 0)
	{
		if (list->prev)
			close(prev_pipe);
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

void	handle_fd_closing(t_list *list, int *pip, int prev_pipe)
{
	if (list->next)
	{
		close(pip[READ]);
		close(pip[WRITE]);
	}
	if (list->prev)
		close(prev_pipe);
	close_files(list);
}

void	child_process(t_list *list, int *pip, int prev_pipe, t_env **env, char **environment)
{
	int	exitcode;

	reset_signals();
	exitcode = check_invalid_file_cmd(list);
	if (exitcode != 0)
	{
		handle_fd_closing(list, pip, prev_pipe);
		exit(exitcode);
	}
	setup_input(list, pip, prev_pipe);
	setup_output(list, pip);
	if (is_builtin(list->cmd))
	{
		exitcode = execute_builtin(list, env, environment);
		exit (exitcode);
	}
	else
		execve(list->cmd, list->args, environment);
}