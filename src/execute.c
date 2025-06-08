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

void	put_flags(t_list **list)
{
	char	*cmd;
	int		flagc;
	char	**flags;

	cmd = get_cmd((*list)->arg);
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
	(*list)->flags = flags;
}

//changes stdoutput into pipe write end and makes sure next node has the pipe
void	handle_pipe_write(t_list **list)
{
	int	pip[2];

	if (!*list)
		return ;
	if (pipe(pip) == -1)
		error_message("pipe error", 1);
	close(pip[READ]);
	dup2(pip[WRITE], STDOUT_FILENO);
	close(pip[WRITE]);
	if ((*list)->next)//make sure the next node has the pipe
	{
	(*list)->next->pip[0] = pip[0];
	(*list)->next->pip[1] = pip[1];
	}
}

//forks and executes execve
void	child_process_pipe_in(t_list **list, char **flags, char **envp)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		error_message("fork error", 1);
	if (pid == 0)
	{
		handle_pipe_write(list);
		if (execve(flags[0], flags, envp) == -1)
			error_message("execve error", 1);
	}
	status = 0;
	waitpid(pid, &status, 0);
}

//just works with one pipe for now...
void	handle_pipe_read(t_list **list)
{
	if (!*list)
		error_message("no tokens after pipe?", 1);
	if ((*list)->pip[0] == -1 || ((*list)->pip[1] == -1))
		error_message("no pipe?", 1);
	dup2((*list)->pip[READ], STDIN_FILENO);
	close ((*list)->pip[READ]);//im not sure if we need to store this pipe as maybe the output of this can be piped again...
}

void	child_process_pipe_out(t_list **list, char **flags, char **envp)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		error_message("fork error", 1);
	if (pid == 0)
	{
		handle_pipe_read(list);
		if (execve(flags[0], flags, envp) == -1)
			error_message("execve error", 1);
	}
	status = 0;
	waitpid(pid, &status, 0);
}

void	execute_pipe(t_list **list, char **envp)
{
	int	pip[2];

	pip[0] = (*list)->pip[0];
	pip[1] = (*list)->pip[1];
	if ((*list)->pip[0] == -1 || ((*list)->pip[1] == -1))
		error_message("no pipe?", 1);
	*list = (*list)->next;//we will also execute here
	put_flags(list);
	if (*list)
	{
		(*list)->pip[0] = pip[0];
		(*list)->pip[1] = pip[1];
	}
	child_process_pipe_out(list, (*list)->flags, envp);
}

void	execute_command(t_list **list, char **envp)
{
	put_flags(list);
	child_process_pipe_in(list, (*list)->flags, envp);
}

int	execute(t_list **list)
{
	while ((*list))
	{
		if ((*list)->arg_type == BUILTIN)
		{
		// 	// execute_builtin(&(*list));
		}
		else if ((*list)->arg_type == COMMAND)
		{
			execute_command(list, (*list)->envp);
		}
		else if ((*list)->arg_type == PIPE)
		{
			execute_pipe(list, (*list)->envp);
		}
		else if ((*list)->arg_type == REDIRECTION)
		{
		// 	// execute_direction();
		}
		*list = (*list)->next;
	}
	return (0);
}

// void	child_process(t_list **list, char **envp)
// {
// 	char	*cmd;
// 	int		flagc;
// 	char	**flags;

// 	handle_pipe_input(list);
// 	cmd = get_cmd((*list)->arg);
// 	if (!cmd)
// 		error_message("malloc error", 1);
// 	(*list)->arg = cmd;
// 	flagc = flag_count(list);
// 	flags = get_flags(flagc, list);
// 	if (!flags)
// 	{
// 		free(cmd);
// 		error_message("malloc error", 1);
// 	}
// 	if (access(cmd, X_OK) == -1)
// 		error_message("access execute error", 126);
// 	handle_pipe_output(list);
// 	if (execve(flags[0], flags, envp) == -1)
// 		error_message("execve error", 127);
// }


// void	execute_command(t_list **list, char **envp)
// {
// 	int	pid;
// 	int	status;

// 	pid = fork();
// 	if (pid == -1)
// 		error_message("fork fail", -1);
// 	if (pid != 0)
// 		child_process(list, envp);
// 	status = 0;
// 	waitpid(pid, &status, 0);
// }