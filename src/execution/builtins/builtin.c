/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:06:12 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/26 15:48:00 by mmisumi          ###   ########.fr       */
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
	else if (ft_strncmp(cmd, "exit", 6) == 0)
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
		return (execute_exit(list));
	return (0);
}

int	reset_stdin_stdout(int stdin, int stdout)
{
	if (stdin != -1)
	{
		if (dup2(stdin, STDIN_FILENO) == -1)
			return (-1);
		close(stdin);
	}
	if (stdout != -1)
	{
		if (dup2(stdout, STDOUT_FILENO) == -1)
			return (-1);
		close(stdout);
	}
	return (0);
}

int	redirect_stdin_stdout(t_list *list, int stdin, int stdout)
{
	if (list->input >= 0)
	{
		stdin = dup(STDIN_FILENO);
		if (stdin == -1)
			return (-1);
		if (dup2(list->input, STDIN_FILENO) == -1)
			return (-1);
		close (list->input);
	}
	if (list->output >= 0)
	{
		stdout = dup(STDOUT_FILENO);
		if (stdout == -1)
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
	int	stdin;
	int	stdout;
	
	stdin = -1;
	stdout = -1;
	exitcode = check_invalid_file_cmd(list, *env);
	if (exitcode == 0)
	{
		if (redirect_stdin_stdout(list, stdin, stdout) == -1)
			return (1);
		exitcode = execute_builtin(list, env, environment);
		if (reset_stdin_stdout(stdin, stdout) == -1)
			return (1);
	}
	if (exitcode != 0)
		close_files(list);
	return (exitcode);
}
