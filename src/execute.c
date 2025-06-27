/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:33 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/13 12:49:44 by mmisumi          ###   ########.fr       */
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

// close read of pipe and set stdin to prevpip 
// void    child_process(t_list *list, int *pip, int pip_input)
// {
//         dup2(pip_input, STDIN_FILENO);
//         close(pip_input);
// 		if (list->next)
// 		{
// 			close(pip[READ]);
// 			dup2(pip[WRITE], STDOUT_FILENO);
// 			close(pip[WRITE]);
// 		}
// 		// if (access())
// }

void    child_process(t_list *list, int *pip, int prev_pipe, char **envp)
{
	if (list->input == -1 && list->output == -1)
		close(prev_pipe);
	if (list->input != -1 && list->output != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
    if (list->next)
	{
		close(pip[READ]);
		dup2(pip[WRITE], STDOUT_FILENO);
		close(pip[WRITE]);
	}
	// check access for exitcodes?
	execve(list->cmd, list->args, envp);
	error_message("execve fail", -1);
}


void    execute(t_list *list, char **envp)
{
    int     pid_count = count_pids(list);
    pid_t   pid[pid_count];
    int     pip[2];
    int     prev_pipe;
    int     i;

    prev_pipe = -1;
    i = 0;
    while (i < pid_count)
    {
        if (list->next && pipe(pip) == -1)
                error_message("pipe_error", -1);
        pid[i] = fork();
        if (pid[i] == -1)
            error_message("fork error", -1);
		printf("forking pid[%d]\n", i);
        if (pid[i] == 0)
            child_process(list, pip, prev_pipe, envp);
		// sets prev pipes stdin for next command, if there is one
		if (list->next)
		{
			prev_pipe = pip[READ];
			close(pip[READ]);
			close(pip[WRITE]);
		}
		// if theres no list->next theres no pipe
		if (!list->next)
			close(prev_pipe);
		i++;
    }
}

int main(int argc, char *argv[], char *envp[])
{
    (void)argc;
    (void)argv;
    t_list *list = NULL;
    char *s = " cat err.log > outfile  | wc -l > outfile2 | echo hello > yolo > yolo2 ";
    list = get_list(list, s, envp);
    if (!list)
    {
        printf("no list\\n");
        return (0);
    }
    print_list(list);
    printf("pid_count: %d\n", count_pids(list));
	execute(list, envp);
    return (0);
}