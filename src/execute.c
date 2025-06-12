/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:33 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/10 16:41:02 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in here we update the pipe
// void	handle_pipe(t_list **list)
// {
// 	//should we handle case where pipe is last argument?
// 	if ((*list)->next && (*list)->prev)
// 	{
// 		(*list)->old_pip[READ] = (*list)->prev->old_pip[READ];
// 		(*list)->old_pip[WRITE] = (*list)->prev->old_pip[WRITE];
// 		printf("listpointer pipe: %s\n", (*list)->arg);
// 	}
// }

// void	child_process(t_list **list, int *new_pip)
// {
// 	char	**flags;

// 	close(new_pip[READ]);
// 	if ((*list)->prev)
// 	{
// 		close((*list)->prev->old_pip[WRITE]);
// 		dup2((*list)->prev->old_pip[READ], STDIN_FILENO);
// 		close((*list)->prev->old_pip[READ]);
// 	}
// 	flags = put_flags(list);
// 	if (!flags)
// 		error_message("malloc error", 1);
// 	print_arr(flags);
// 	if ((*list)->next)
// 		dup2(new_pip[WRITE], STDOUT_FILENO);
// 	close(new_pip[WRITE]);
// 	execve(flags[0], flags, (*list)->envp);
// 	error_message("execve error", 1);
// 	perror("execve: ");
// 	exit(1);
// }

// int	execute(t_list **list)
// {
// 	while ((*list))
// 	{
// 		if ((*list)->arg_type == BUILTIN)
// 		{
// 			// 	// execute_builtin(&(*list));
// 		}
// 		else if ((*list)->arg_type == COMMAND)
// 		{
// 			execute_command(list);
// 		}
// 		else if ((*list)->arg_type == PIPE)
// 		{
// 			handle_pipe(list);
// 		}
// 		else if ((*list)->arg_type == REDIRECTION)
// 		{
// 			// 	// execute_direction();
// 		}
// 		*list = (*list)->next;
// 	}
// 	// wait(NULL);
// 	return (0);
// }


// void	execute_command(t_list **list)
// {
// 	int	new_pip[2];
// 	int	pid;

// 	if (pipe(new_pip) == -1)
// 		error_message("pipe error", 1);
// 	pid = fork();
// 	if (pid == -1)
// 		error_message ("fork error", 1);
// 	if (pid == 0)
// 		child_process(list, new_pip);
// 	if ((*list)->prev)
// 		close((*list)->prev->old_pip[READ]);
// 	(*list)->old_pip[READ] = new_pip[READ];
// 	(*list)->old_pip[WRITE] = new_pip[WRITE];
// 	close(new_pip[WRITE]);

// }
// void	child_process(t_list *node, int *prev_pipe, int *new_pipe)
// {
// 	char **flags;

// 	if (prev_pipe) {
// 		close(prev_pipe[WRITE]);
// 		dup2(prev_pipe[READ], STDIN_FILENO);
// 		close(prev_pipe[READ]);
// 	}
// 	if (new_pipe) {
// 		close(new_pipe[READ]);
// 		dup2(new_pipe[WRITE], STDOUT_FILENO);
// 		close(new_pipe[WRITE]);
// 	}
// 	flags = put_flags(&node);
// 	if (!flags)
// 		error_message("malloc error", 1);
// 	execve(flags[0], flags, node->envp);
// 	error_message("execve error", 1);
// }

// void	execute_command(t_list *node, int *prev_pipe)
// {
// 	int new_pipe[2];
// 	int *curr_pipe = NULL;
// 	int pid;

// 	if (node->next && node->next->arg_type == COMMAND) {
// 		curr_pipe = new_pipe;
// 		if (pipe(new_pipe) == -1)
// 			error_message("pipe error", 1);
// 	}

// 	pid = fork();
// 	if (pid == -1)
// 		error_message("fork error", 1);

// 	if (pid == 0)
// 		child_process(node, prev_pipe, curr_pipe);

// 	// parent
// 	if (prev_pipe) {
// 		close(prev_pipe[READ]);
// 		close(prev_pipe[WRITE]);
// 	}
// 	if (curr_pipe) {
// 		// keep read end for next command
// 		node->old_pip[READ] = curr_pipe[READ];
// 		node->old_pip[WRITE] = curr_pipe[WRITE]; // may not need WRITE
// 		close(curr_pipe[WRITE]); // parent doesn't write
// 	}
// }

void	child_process(t_list **list, int *new_pipe, t_list *prev)
{
	char	**flags;
	if (prev && prev->pipe[READ] != -1)
	{
		close(prev->pipe[WRITE]);
		dup2(prev->pipe[READ], STDIN_FILENO);
		close(prev->pipe[READ]);
	}
	flags = put_flags(list);
	if (!flags)
		error_message("malloc error", 1);
	print_arr(flags);
	if (new_pipe[WRITE] != -1)
	{
		close(new_pipe[READ]);
		if ((*list)->next)
			dup2(new_pipe[WRITE], STDOUT_FILENO);
		close(new_pipe[WRITE]);
	}
	if (execve(flags[0], flags, (*list)->envp) == -1)
		error_message("execve error", 1);
	perror("execve:");
}

void	execute_command(t_list **list)
{
	t_list	*prev;
	int		new_pipe[2] = {-1, -1};
	pid_t	pid;

	prev = (*list)->prev;
	if (prev && prev->pipe[WRITE] != -1)
		close(prev->pipe[WRITE]);
	if ((*list)->next)
	{
		if (pipe(new_pipe) == -1)
			error_message("pipe error", 1);
	}
	pid = fork();
	if (pid == -1)
		error_message("fork error", 1);
	if (pid == 0)
		child_process(list, new_pipe, prev);
	if (prev && prev->pipe[READ] != -1)
		close(prev->pipe[READ]);	
	(*list)->pipe[READ] = new_pipe[READ];
	(*list)->pipe[WRITE] = new_pipe[WRITE];
}


int	execute(t_list **list)
{
	while (*list)
	{
		if ((*list)->arg_type == COMMAND)
		{
			execute_command(list);
		}
		*list = (*list)->next;
	}
	wait(NULL);
	return (0);
}

// int	execute(t_list **list)
// {
// 	t_list *curr = *list;
// 	int *prev_pipe = NULL;

// 	while (curr)
// 	{
// 		if (curr->arg_type == COMMAND)
// 		{
// 			execute_command(curr, prev_pipe);
// 			prev_pipe = curr->old_pip; // pass for next command
// 		}
// 		else if (curr->arg_type == PIPE)
// 		{
// 			// optional depending on your design
// 		}
// 		curr = curr->next;
// 	}
// 	while (wait(NULL) > 0) {}
// 	return (0);
// }