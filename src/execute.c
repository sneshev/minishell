// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   execute.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/02 16:01:33 by mmisumi           #+#    #+#             */
// /*   Updated: 2025/06/13 12:49:44 by mmisumi          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// void	child_process(t_list **list, int *new_pipe, t_list *prev)
// {
// 	char	**flags;
// 	if (prev && prev->pipe[READ] != -1)
// 	{
// 		close(prev->pipe[WRITE]);
// 		dup2(prev->pipe[READ], STDIN_FILENO);
// 		close(prev->pipe[READ]);
// 	}
// 	flags = put_flags(list);
// 	if (!flags)
// 		error_message("malloc error", 1);
// 	print_arr(flags);
// 	if (new_pipe[WRITE] != -1)
// 	{
// 		close(new_pipe[READ]);
// 		if ((*list)->next)
// 			dup2(new_pipe[WRITE], STDOUT_FILENO);
// 		close(new_pipe[WRITE]);
// 	}
// 	if (execve(flags[0], flags, (*list)->envp) == -1)
// 		error_message("execve error", 1);
// 	perror("execve:");
// }

// void	execute_command(t_list **list)
// {
// 	t_list	*prev;
// 	int		new_pipe[2] = {-1, -1};
// 	pid_t	pid;

// 	prev = (*list)->prev;
// 	if (prev && prev->pipe[WRITE] != -1)
// 		close(prev->pipe[WRITE]);
// 	if ((*list)->next)
// 	{
// 		if (pipe(new_pipe) == -1)
// 			error_message("pipe error", 1);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 		error_message("fork error", 1);
// 	if (pid == 0)
// 		child_process(list, new_pipe, prev);
// 	if (prev && prev->pipe[READ] != -1)
// 		close(prev->pipe[READ]);	
// 	(*list)->pipe[READ] = new_pipe[READ];
// 	(*list)->pipe[WRITE] = new_pipe[WRITE];
// }


// int	execute(t_list **list)
// {
// 	while (*list)
// 	{
// 		if ((*list)->arg_type == COMMAND)
// 		{
// 			execute_command(list);
// 		}
// 		*list = (*list)->next;
// 	}
// 	wait(NULL);
// 	return (0);
// }
