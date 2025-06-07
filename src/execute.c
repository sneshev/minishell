/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:33 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/05 12:28:42 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
}

void	child_process(t_list **list, char **envp)
{
	char	*cmd;
	int		flagc;
	char	**flags;

	cmd = get_cmd((*list)->arg, envp);
	if (!cmd)
		error_message("malloc error", 1);
	(*list)->arg = cmd;
	flagc = flag_count(list);
	flags = get_flags(flagc, list);
	if (!flags)
	{
		free(cmd);
		error_message("malloc error", 1);
	}
	if (access(cmd, X_OK) == -1)
		error_message("access execute error", 126);
	if (execve(flags[0], flags, envp) == -1)
		error_message("execve error", 127);
}

void	execute_command(t_list **list, char **envp)
{
	int	pid;
	int	pip[2];
	int	status;

	if (pipe(pip) == -1)
		error_message("pipe error", 1);
	close(pip[READ]);
	pid = fork();
	if (pid == -1)
		error_message("fork fail", -1);
	if (pid == 0)
		child_process(list, envp);
	// status = 0;
	// waitpid(pid, &status, 0);
	// if (WIFEXITED(status))
	// 	return (WEXITSTATUS(status));
	wait(NULL);
}

int	execute(t_list **list)
{
	while ((*list))
	{
		if ((*list)->arg_type == BUILTIN)
		{
			print_list(*list);
		// 	// execute_builtin(&(*list));
		}
		else if ((*list)->arg_type == COMMAND)
		{
			print_list((*list));
			execute_command(&(*list), (*list)->envp);
		}
		else if ((*list)->arg_type == PIPE)
		{
			print_list((*list));
		// 	// execute_pipe();
		}
		else if ((*list)->arg_type == REDIRECTION)
		{
			print_list(*list);
		// 	// execute_direction();
		}
		*list = (*list)->next;
	}
	return (0);
}
