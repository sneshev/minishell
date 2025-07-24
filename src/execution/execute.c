/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:39:33 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/24 17:42:03 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

void	handle_setup_close(t_list *list, int *pip, int *pipe_input)
{
	if (list->prev)
	close(*pipe_input);
	if (list->next)
	{
		*pipe_input = pip[READ];
		close(pip[WRITE]);
	}
	if (!list->next && *pipe_input != -1)
	close(*pipe_input);
}

int	execute_list(t_list *list, int pid_count, t_env **env, char **environment)
{
	pid_t	pid[pid_count];
	int		pip[2];
	int		pipe_input;
	int		i;
	int		exitcode;
	
	i = 0;
	pipe_input = -1;
	while (i < pid_count)
	{
		if (list->next)
		{
			if (pipe(pip) == -1)
			perror_message("pipe");
		}
		pid[i] = fork();
		if (pid[i] == CHILD)
			child_process(list, pip, pipe_input, env, environment);
		handle_setup_close(list, pip, &pipe_input);
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
	
	disable_SIGINT();
	environment = convert_env(*env);
	if (!environment)
	return (-1);
	if (!list->next && is_builtin(list->cmd))
	{

		exitcode = execute_builtin_parent(list, env, environment);
		return (free_arr(environment), exitcode);
	}
	exitcode = execute_list(list, count_pids(list), env, environment);
	return (free_arr(environment), exitcode);
}


// int	check_invalid_file_cmd(t_list *list)
// {
// 	if (list->input == -1 && list->output == -1)
// 		return (1);
// 	if (is_builtin(list->cmd))
// 		return (0);
// 	else if (ft_strchr(list->cmd, '/'))
// 	{
// 		if (is_directory(list->cmd))
// 		{
// 			// write_err(list->cmd, "is a directory\n");
// 			return (126);
// 		}
// 		else if (access(list->cmd, F_OK) == -1)
// 			return (127);
// 		else if (access(list->cmd, X_OK) == -1)
// 		{
// 			// write_err(list->cmd, "Permission denied");
// 			return (126);
// 		}
// 	}
// 	else
// 	{
// 		// write_err(list->cmd, "command not found\n");
// 		return (127);
// 	}
// 	return (0);
// }