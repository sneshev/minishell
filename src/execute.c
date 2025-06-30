/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:33 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/30 15:45:21 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get the amount of commandnodes so we know the amount we need to fork
int count_pids(t_list *list)
{
    int count;

    count = 0;
    while (list)
    {
        list = list->next;
        count++;
    }
    return (count);
}

void	setup_input(t_list *list, int *prev_pipe)
{
	if (list->input == -2)
	{
		if (list->prev)
		{
			dup2(*prev_pipe, STDIN_FILENO);
			close (*prev_pipe);
		}
	}
	if (list->input >= 0)
	{
		dup2(list->input, STDIN_FILENO);
		close (list->input);
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
	if (list->output >= 0)
	{
		dup2(list->output, STDOUT_FILENO);
		close(list->output);
	}
}

void	child_process(t_list *list, int *pip, int *prev_pipe, char **envp)
{
	if (list->input == -1 && list->output == -1)
	{
		if (list->prev)
			close (*prev_pipe);
		if (list->next)
		{
			close(pip[WRITE]);
			close(pip[READ]);
		}
		exit(1) ;
	}
	setup_input(list, prev_pipe);
	setup_output(list, pip);

	execve(list->cmd, list->args, envp);
	error_message("execve_fail", 127);
}

void	handle_setup_close(t_list *list, int *pip, int prev_pipe)
{
	// there is no next list so we close everything
	if (!list->next)
	{
		if (list->prev)
		{
			close(prev_pipe);
			close(pip[READ]);
			close(pip[WRITE]);
		}
			// if there is a list next, obviously we are not closing everything	
	}
	if (list->next)
	{
		if (list->prev)
			close(prev_pipe);
		prev_pipe = pip[READ];
		close(pip[WRITE]);
	}
}

void	execute(t_list *list, char **envp, int pid_count)
{
	pid_t	pid[pid_count];
	int		pip[2];
	int		pipe_input;
	int		i;

	pipe_input = -1;
	i = 0;
	while (i < pid_count)
	{
		if (list->next)
		{
			if (pipe(pip) == -1)
				error_message("pipe error", -1);
		}
		pid[i] = fork();
		if (pid[i] == -1)
			error_message("fork error", -1);
		if (pid[i] == 0)
			child_process(list, pip, &pipe_input, envp);
		handle_setup_close(list, pip, pipe_input);

		list = list->next;
		i++;
	}
}


// int main(int argc, char *argv[], char *envp[])
// {
//     (void)argc;
//     (void)argv;
//     t_list *list = NULL;
//     char *s = "cat < invalid > outfile | cat err.log > outfile";
//     list = get_list(list, s, envp);
//     if (!list)
//     {
//         printf("no list\\n");
//         return (0);
//     }
//     print_list(list);
//     printf("pid_count: %d\n", count_pids(list));
// 	execute(list, envp, count_pids(list));
//     return (0);
// }