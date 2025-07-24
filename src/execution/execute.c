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

void	close_files(t_list *list)
{
	if (list->input >= 0)
		close(list->input);
	if (list->output >= 0)
		close(list->output);
}

void	handle_fd_closing(t_list *list, int *pip, int prev_pipe)
{
	if (list->next)
	{
		close(pip[READ]);
		close(pip[WRITE]);
	}
	if (list->prev)
		close(prev_pipe);
	close_files(list);
}

int	check_access(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == -1)
				return (write_err(cmd, "Permission denied"), 126);
			return (0);
		}
		write_err(cmd, "No such file or directory");
		return (127);
	}
	else
	{
		if (access(cmd, F_OK) == 0)
		{
			//check for is a directory
			if (access(cmd, X_OK) == -1)
				return (write_err(cmd, "Permission denied"), 126);
			return (0);
		}
		write_err(cmd, "command not found");
		return (127);
	}
}

int	check_invalid_file_cmd(t_list *list)
{
	if (list->input == -1 && list->output == -1)
		return (1);
	if (is_builtin(list->cmd))
		return (0);
	return (check_access(list->cmd));
	// else if (check_access(list->cmd) == 0)

	// else if (access(list->cmd, F_OK) == -1)
	// 	return (127);
	// else if (access(list->cmd, X_OK) == -1)
	// {
	// 	write_err(list->cmd, "Permission denied\n");
	// 	return (126);
	// }
	// return (0);
}

// int	check_invalid_file_cmd(t_list *list)
// {
// 	if (list->input == -1 && list->output == -1)
// 		return (1);
// 	if (is_builtin(list->cmd))
// 		return (0);
// 	else if (ft_strchr(list->cmd, '/'))
// 	{
// 		if (is_directory(list->cmd))
// 		{
// 			// write_err(list->cmd, "is a directory\n");
// 			return (126);
// 		}
// 		else if (access(list->cmd, F_OK) == -1)
// 			return (127);
// 		else if (access(list->cmd, X_OK) == -1)
// 		{
// 			// write_err(list->cmd, "Permission denied");
// 			return (126);
// 		}
// 	}
// 	else
// 	{
// 		// write_err(list->cmd, "command not found\n");
// 		return (127);
// 	}
// 	return (0);
// }

void	child_process(t_list *list, int *pip, int prev_pipe, t_env *env, char **environment)
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
	if (ft_strcmp(list->cmd, "echo") == 0 || ft_strcmp(list->cmd, "pwd") == 0)
	{
		execute_builtin(list, NULL, NULL);
		exit (0);
	}
	else if (!list->args[1] && ft_strcmp(list->cmd, "env") == 0)
	{
		print_env(environment);
		exit (0);
	}
	else if (!list->args[1] && ft_strcmp(list->cmd, "export") == 0)
	{
		print_export(env);
		exit (0);
	}
	else if (is_builtin(list->cmd))
		exit (0);
	else
		execve(list->cmd, list->args, environment);
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

int	execute_list(t_list *list, int pid_count, t_env **env, char **environment)
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
			child_process(list, pip, pipe_input, *env, environment);
		handle_setup_close(list, pip, &pipe_input);
		close_files(list);

		list = list->next;
		i++;
	}
	exitcode = wait_for_pids(pid, pid_count);
	return (exitcode);
}

void	reset_stdin_stdout(int save_std[2])
{
	if (save_std[0] != -1)
	{
		dup2(save_std[0], STDIN_FILENO);
		close(save_std[0]);
	}
	if (save_std[1] != -1)
	{
		dup2(save_std[1], STDOUT_FILENO);
		close(save_std[1]);
	}
}

int	execute_builtin_parent(t_list *list, t_env **env, char **environment)
{
	int	exitcode;
	int	save_std[2];

	save_std[0] = -1;
	save_std[1] = -1;
	exitcode = check_invalid_file_cmd(list);
	if (exitcode == 0)
	{
		if (list->input >= 0)
		{
			save_std[0] = dup(STDIN_FILENO);
			dup2(list->input, STDIN_FILENO);
			close (list->input);
		}
		if (list->output >= 0)
		{
			save_std[1] = dup(STDOUT_FILENO);
			dup2(list->output, STDOUT_FILENO);
			close(list->output);
		}
		exitcode = execute_builtin(list, env, environment);
		reset_stdin_stdout(save_std);
	}
	if (exitcode != 0)
		close_files(list);
	return (exitcode);
}

int	execute(t_list *list, t_env **env)
{
	char	**environment;
	int		exitcode;

	disable_SIGINT();
	environment = convert_env(*env);
	if (!environment)
		return (-1);
	if (!list->next && is_builtin(list->cmd))
	{
		exitcode = execute_builtin_parent(list, env, environment);
		return (free_arr(environment), exitcode);
	}
	exitcode = execute_list(list, count_pids(list), env, environment);
	return (free_arr(environment), exitcode);
}
