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

int	check_invalid_file(t_list *list, int *pip, int prev_pipe)
{
	if (list->input == -1 && list->output == -1)
	{
		if (list->next)
		{
			close(pip[READ]);
			close(pip[WRITE]);
		}
		if (list->prev)
			close(prev_pipe);
		return (-1);
	}
	return (0);
}

int	check_invalid_cmd(t_list *list, int *pip, int prev_pipe)
{
	int	x;

	x = 0;
	if (access(list->cmd, F_OK) == -1 || access(list->cmd, X_OK == -1))
		x++;
	if (!is_builtin(list->cmd))
		x++;
	// if x == 2 it means its an invalid cmd
	if (x == 2)
	{
		perror_message(list->cmd);
		if (list->next)
		{
			close(pip[READ]);
			close(pip[WRITE]);
		}
		if (list->prev)
			close(prev_pipe);
		return (-1);
	}
	return (0);
}

void	child_process(t_list *list, int *pip, int prev_pipe, char **environment)
{
	reset_signals();
	if (check_invalid_file(list, pip, prev_pipe) == -1)
		exit (1);
	else if (check_invalid_cmd(list, pip, prev_pipe) == -1)
		exit (1);
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
	reset_signals();
	return (exitcode);
}

void	close_files(t_list *list)
{
	if (list->input >= 0)
		close(list->input);
	if (list->output >= 0)
		close(list->output);
}

int	execute(t_list *list, t_env **env, int pid_count)
{
	pid_t	pid[pid_count];
	int		pip[2];
	int		pipe_input;
	int		i;
	char	**environment;

	disable_SIGINT();
	environment = convert_env(*env); // never freed
	if (!environment)
		return -1;
	pipe_input = -1;
	i = 0;
	if (!list->next && (is_builtin(list->cmd)))
	{
		if (check_invalid_file(list, pip, pipe_input) == -1)
			return (1);
		else if (check_invalid_cmd(list, pip, pipe_input) == -1)
			return (1);
		execute_builtin(list, env, environment);
		return (0);
	}
	while (i < pid_count)
	{
		if (list->next && pipe(pip) == -1)
			error_message("pipe error", -1);
		pid[i] = fork();
		if (pid[i] == -1)
			error_message("fork error", -1);
		if (pid[i] == CHILD)
			child_process(list, pip, pipe_input, environment);
		handle_setup_close(list, pip, &pipe_input);
		close_files(list);

		list = list->next;
		i++;
	}
	return (wait_for_pids(pid, pid_count));
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