/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:33 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/28 14:13:21 by mmisumi          ###   ########.fr       */
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

void	child_process(t_list *list, int *pip, int prev_pipe)
{
	// if infile is stdin
	if (list->input >= 0)
	{
		dup2(list->input, STDIN_FILENO);
		close (list->input);
		close(pip[READ]);
		// close prev_pipe if it exists
		if (prev_pipe != -1)
			close (prev_pipe);
	}
	// if we have no infile as stdin
	else if (list->input < 0)
	{
		// if we have a prev pipe
		if (prev_pipe != -1)
		{
			dup2(prev_pipe, STDIN_FILENO);
			close(prev_pipe);
		}
		// if we have no infile or pipe input, we simply close
		close(pip[READ]);
	}
	// if theres an outfile to redirect to
	if (list->output >= 0)
	{
		dup2(list->output, STDOUT_FILENO);
		close (list->output);
		close(pip[WRITE]);
	}
	// if theres no outfile
	else if (list->output < 0)
	{
		// if there is a next node, meaning there is a pipe
		if (list->next)
			dup2(pip[WRITE], STDOUT_FILENO);
		// no outfile and pipe output, we simply close and write to terminal
		close(pip[WRITE]);
	}
	


}

// check for invalid files -> we will then not enter the child process and go right to the next list
// if files are valid, and theres a list->next, we pipe and enter child process (prev_pipe is still -1 so its doesnt exist yet)
// we check if theres an infile/outfile by checking its value, if this is -2 we dont set it up as it doesnt exist
// if theres an infile we dup2 this to stdin and close prev_pipe if this is not -1
// if theres an outfile we dup2 this to stdout and close all pipe ends (if theres a list->next; meaning we piped)
// if there is no infile and outfile we will setup the prev_pip and pip[WRITE] to stdin and stdout and closing other ends accordingly
// if we are at te last node we have to close everything:
//	.if prev_pipe != -1 close, if (list->prev close pip[READ] && pip[WRITE])

void	execute(t_list *list, char **envp, int pid_count)
{
	pid_t	pid[pid_count];
	int		pip[2];
	int		prev_pipe;
	int		i;

	prev_pipe = -1;
	i = 0;
	while (i < pid_count)
	{
		execute_command(list, prev_pipe, pip, pid[i], envp);
		i++;
	}
}

void	execute_command(t_list *list, int prev_pipe, int *pip, int pid, char **envp)
{
	// check if the node is valid and we can continue executing
	if (list->input != -1 && list->output != -1)
	{
		// we pipe if there is more than one list
		if (list->next && pipe(pip) == -1)
			error_message("pipe error", -1);
		pid = fork();
		if (pid == -1)
			error_message("fork error", -1);
		if (pid == 0)
			child_process();
		// if we piped
		if (list->next)
		{
			prev_pipe = pip[READ];
			close(pip[READ]);
			close(pip[WRITE]);
		}
		// if we didnt pipe
		if (!list->next)
			close(prev_pipe);
		// we already closed in child when calling dup2 but must be also in parent
		if (list->input >= 0)
			close(list->input);
		if (list->output >= 0)
			close(list->output);
	}
}

void	child_process()
{

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
	execute(list, envp, count_pids(list));
    return (0);
}