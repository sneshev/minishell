#include "../minishell.h"
#include "execution.h"

int	count_pids(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		list = list->next;
		count++;
	}
	return (count);
}

void	setup_input(t_list *list, int *pip, int prev_pipe)
{
	if (list->next)
		close(pip[READ]);
	if (list->input == -2)
	{
		if (list->prev)
		{
			dup2(prev_pipe, STDIN_FILENO);
			close(prev_pipe);
		}
	}
	else if (list->input >= 0)
	{
		if (list->prev)
			close(prev_pipe);
		dup2(list->input, STDIN_FILENO);
		close(list->input);
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
	else if (list->output >= 0)
	{
		dup2(list->output, STDOUT_FILENO);
		close(list->output);
		if (list->next)
			close(pip[WRITE]);
	}
}

void	handle_fd_closing(t_list *list, int *pip, int prev_pipe)
{
	perror_message(list->cmd);
	if (list->next)
	{
		close(pip[READ]);
		close(pip[WRITE]);
	}
	if (list->prev)
		close(prev_pipe);
}

int	check_invalid_file_cmd(t_list *list)
{
	if (list->input == -1 && list->output == -1)
		return (1);
	if (access(list->cmd, F_OK) == -1)
		return (127);
	else if (access(list->cmd, X_OK) == -1)
		return (126);
	return (0);
}

void	child_process(t_list *list, int *pip, int prev_pipe, char **environment)
{
	int	exitcode;

	reset_signals();
	exitcode = check_invalid_file_cmd(list);
	if (exitcode != 0)
	{
		handle_fd_closing(list, pip, prev_pipe);
		exit(exitcode);
	}
	setup_input(list, pip, prev_pipe);
	setup_output(list, pip);
	if (ft_strncmp(list->cmd, "echo", 5) == 0)
		execute_echo(list);
	else if (ft_strncmp(list->cmd, "pwd", 4) == 0)
		execute_pwd();
	else if (ft_strncmp(list->cmd, "env", 4) == 0)
		execute_env(list, environment);
	else
	{
		execve(list->cmd, list->args, environment);
		printf("execve error");
	}
}

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

int	wait_for_pids(pid_t *pid, int pid_count)
{
	int	i;
	int	status;
	int	exitcode;

	i = 0;
	status = 0;
	exitcode = 0;
	while (i < pid_count - 1)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WEXITSTATUS(status))
		exitcode = (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
		else if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}

	return (exitcode);
}

void	close_files(t_list *list)
{
	if (list->input >= 0)
		close(list->input);
	if (list->output >= 0)
		close(list->output);
}

int	execute_list(t_list *list, int pid_count, char **environment)
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
			child_process(list, pip, pipe_input, environment);
		handle_setup_close(list, pip, &pipe_input);
		close_files(list);

		list = list->next;
		i++;
	}
	exitcode = wait_for_pids(pid, pid_count);
	return (exitcode);
}

int	execute_builtin_parent(t_list *list, t_env **env, char **environment)
{
	int	exitcode;

	exitcode = check_invalid_file_cmd(list);
	if (exitcode == 0)
		execute_builtin(list, env, environment);
	return (exitcode);
}

int	execute(t_list *list, t_env **env)
{
	char	**environment;
	int		exitcode;

	disable_SIGINT();
	environment = convert_env((*env)->next);
	if (!environment)
		return (-1);
	if (!list->next && is_builtin(list->cmd))
	{
		exitcode = check_invalid_file_cmd(list);
		if (exitcode == 0)
			execute_builtin(list, env, environment);
		// exitcode = execute_builtin_parent(list, env, environment);
		close_files(list);
		return (free_arr(environment), exitcode);
	}
	exitcode = execute_list(list, count_pids(list), environment);
	free_arr(environment);
	return (exitcode);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	(void)argc;
// 	(void)argv;
// 	t_list	*list = NULL;
// 	char	*s = "cat err.log | cat Makefile > hi < invalid";
// 	list = get_list(list, s, envp);
// 	if (!list)
// 		return (printf("no list\n"), 0);
// 	print_list(list);
// 	execute(list, envp, count_pids(list));
// 	return (0);
// }