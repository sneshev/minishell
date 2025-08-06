/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:06:12 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/26 16:31:15 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../execution.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	else
		return (false);
}

int	execute_builtin(t_list *list, t_env **env, char **environment)
{
	if (ft_strncmp(list->cmd, "echo", 5) == 0)
		return (execute_echo(list));
	else if (ft_strncmp(list->cmd, "cd", 3) == 0)
		return (execute_cd(list, *env));
	else if (ft_strncmp(list->cmd, "pwd", 4) == 0)
		return (execute_pwd());
	else if (ft_strncmp(list->cmd, "export", 7) == 0)
		return (execute_export(list, env));
	else if (ft_strncmp(list->cmd, "unset", 6) == 0)
		return (execute_unset(list, env));
	else if (ft_strncmp(list->cmd, "env", 4) == 0)
		return (execute_env(list, environment));
	else if (ft_strncmp(list->cmd, "exit", 5) == 0)
	{
		if (list->prev == NULL && list->next == NULL)
			return (execute_exit(list, env, environment, false));
		else
			return (execute_exit(list, env, environment, true));
	}
	return (0);
}

int	reset_stdin_stdout(int save_std[2])
{
	if (save_std[0] != -1)
	{
		if (dup2(save_std[0], STDIN_FILENO) == -1)
			return (-1);
		close(save_std[0]);
	}
	if (save_std[1] != -1)
	{
		if (dup2(save_std[1], STDOUT_FILENO) == -1)
			return (-1);
		close(save_std[1]);
	}
	return (0);
}

int	redirect_stdin_stdout(t_list *list, int save_std[2])
{
	if (list->input >= 0)
	{
		save_std[0] = dup(STDIN_FILENO);
		if (save_std[0] == -1)
			return (-1);
		if (dup2(list->input, STDIN_FILENO) == -1)
			return (-1);
		close (list->input);
	}
	if (list->output >= 0)
	{
		save_std[1] = dup(STDOUT_FILENO);
		if (save_std[1] == -1)
			return (-1);
		if (dup2(list->output, STDOUT_FILENO) == -1)
			return (-1);
		close(list->output);
	}
	return (0);
}

int	execute_builtin_parent(t_list *list, t_env **env, char **environment)
{
	int	exitcode;
	int	save_std[2];
	
	save_std[0] = -1;
	save_std[1] = -1;
	exitcode = check_invalid_file_cmd(list, *env);
	if (exitcode == 0)
	{
		if (redirect_stdin_stdout(list, save_std) == -1)
			return (1);
		exitcode = execute_builtin(list, env, environment);
		if (reset_stdin_stdout(save_std) == -1)
			return (1);
	}

	if (exitcode != 0)
		close_files(list);
	return (exitcode);
}
