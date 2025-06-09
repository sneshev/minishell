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

//in here we update the pipe
void	handle_pipe(t_list **list)
{
	//should we handle case where pipe is last argument?
	if ((*list)->next)
	{
		(*list)->next->pip[READ] = (*list)->pip[READ];
		(*list)->next->pip[WRITE] = (*list)->pip[WRITE];
	}
}

//list exists for sure cause we havent changed pointer since pointing to last flag
void	handle_pipe_read(t_list **list)
{
	//should we close write end again?
	dup2((*list)->pip[READ], STDIN_FILENO);
	close ((*list)->pip[READ]);
}

void	handle_pipe_write(t_list **list)
{
	int	pip[2];

	if (pipe(pip) == -1)
		error_message("pipe error", 1);
	close(pip[READ]);
	dup2(pip[WRITE], STDOUT_FILENO);
	close(pip[WRITE]);
	//we write to the pipe(or redirect?)
	(*list)->next->pip[READ] = pip[0];
	(*list)->next->pip[WRITE] = pip[1];
}

//pointer is now at the last flag
void	child_process(t_list **list, char **flags)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid != 0)
	{
		//when we have pipe we will update the pipe to next command
		if ((*list)->pip[READ] > 0 && (*list)->pip[WRITE] > 0)
			handle_pipe_read(list);
		//idk if its better to always write to pipe and then we can always redirect to terminal
		if ((*list)->next)//should we specifically check for command or maybe we also use this for redirect
			handle_pipe_write(list);
		if (execve(flags[0], flags, (*list)->envp) == -1)
			error_message("execve error", 127);
	}
	status = 0;
	waitpid(pid, &status, 0);
}

void	execute_command(t_list **list)
{
	char	**flags;
	flags = put_flags(list);
	if (!flags)
		error_message("malloc error", 1);
	child_process(list, flags);
	free_arr(flags);
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
			execute_command(list);
		}
		else if ((*list)->arg_type == PIPE)
		{
			handle_pipe(list);
		}
		else if ((*list)->arg_type == REDIRECTION)
		{
		// 	// execute_direction();
		}
		*list = (*list)->next;
	}
	return (0);
}
