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
void    child_process(t_list *list, int *pip, int pip_input)
{
        dup2(pip_input, STDIN_FILENO);
        close(pip_input);
		if (list->next)
		{
			close(pip[READ]);
			dup2(pip[WRITE], STDOUT_FILENO);
			close(pip[WRITE]);
		}
		// if (access())
}


void    execute(t_list *list)
{
    int     pid_count = count_pids(list);
    pid_t   pid[pid_count];
    int     pip[2];
    int     pip_input;
    int     i;

    pip_input = -1;
    i = 0;
    while (i < pid_count)
    {
        if (list->next && pipe(pip) == -1)
                error_message("pipe_error", -1);
        pid[pid_count] = fork();
        if (pid[i] == -1)
            error_message("fork error", -1);
        if (pid[i] == 0)
            child_process(list, pip, pip_input);
    }
}


int main(int argc, char *argv[], char *envp[])
{
    (void)argc;
    (void)argv;
    t_list *list = NULL;
    char *s = " cat err.log > outfile  | wc -l > outfile2 ";
    list = get_list(list, s, envp);
    if (!list)
    {
        printf("no list\\n");
        return (0);
    }
    print_list(list);
    printf("pid_count: %d\n", count_pids(list));
    return (0);
}