/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:06:12 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/24 16:41:34 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../execution.h"

bool	is_builtin(char *cmd)
{
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
	else if (ft_strncmp(list->cmd, "exit", 6) == 0)
		return (execute_exit(list));
	return (0);
}

void	reset_stdin_stdout(int save_std[2])
{
	if (save_std[0] != -1)
	{
		dup2(save_std[0], STDIN_FILENO);
		close(save_std[0]);
	}
	if (save_std[1] != -1)
	{
		dup2(save_std[1], STDOUT_FILENO);
		close(save_std[1]);
	}
}

int	execute_builtin_parent(t_list *list, t_env **env, char **environment)
{
	int	exitcode;
	int	save_std[2];
	
	save_std[0] = -1;
	save_std[1] = -1;
	exitcode = check_invalid_file_cmd(list);
	if (exitcode == 0)
	{
		if (list->input >= 0)
		{
			save_std[0] = dup(STDIN_FILENO);
			dup2(list->input, STDIN_FILENO);
			close (list->input);
		}
		if (list->output >= 0)
		{
			save_std[1] = dup(STDOUT_FILENO);
			dup2(list->output, STDOUT_FILENO);
			close(list->output);
		}
		exitcode = execute_builtin(list, env, environment);
		reset_stdin_stdout(save_std);
	}
	if (exitcode != 0)
	close_files(list);
	return (exitcode);
}