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

void	check_invalid_file(t_list *list, int *pip, int prev_pipe)
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
		exit(1);
	}
}

bool	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "exit", 6) == 0)
		return (true);
	else
		return (false);
}

void	execute_builtin(t_list *list, t_env *env)
{
	if (ft_strncmp(list->cmd, "echo", 5) == 0)
		execute_echo(list);
	else if (ft_strncmp(list->cmd, "cd", 3) == 0)
		execute_cd(list);
	else if (ft_strncmp(list->cmd, "pwd", 4) == 0)
		execute_pwd(list);
	else if (ft_strncmp(list->cmd, "export", 7) == 0)
		execute_export(list, env);
	else if (ft_strncmp(list->cmd, "unset", 6) == 0)
		execute_unset(list, env);
	else if (ft_strncmp(list->cmd, "env", 4) == 0)
		execute_env(list, env);
	else if (ft_strncmp(list->cmd, "exit", 6) == 0)
		execute_exit(list);
}

void	child_process(t_list *list, int *pip, int prev_pipe, char **environment)
{
	check_invalid_file(list, pip, prev_pipe);
	setup_input(list, pip, prev_pipe);
	setup_output(list, pip);
	// if (is_builtin(list->cmd))
	// 	execute_builtin(list, environment);
	// else
	// {
		execve(list->cmd, list->args, environment);
		fprintf(stderr, "execve error");
	// }
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

void	wait_for_pids(pid_t *pid, int pid_count)
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
	// exit (exitcode);
}

void	close_files(t_list *list)
{
	if (list->input >= 0)
		close(list->input);
	if (list->output >= 0)
		close(list->output);
}

int	count_env_vars(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**convert_env(t_env *env)
{
	int		vars;
	char	**environment;
	int		i;

	vars = count_env_vars(env);
	environment = malloc(sizeof(char *) * (vars + 1));
	if (!environment)
		return (NULL);
	i = 0;
	while (env)
	{
		environment[i] = ft_strjoin(env->name, env->value);
		if (!environment[i])
			return (free_arr(environment), NULL);
		i++;
		env = env->next;
	}
	return (environment);

}

void	execute(t_list *list, t_env *env, int pid_count)
{
	pid_t	pid[pid_count];
	int		pip[2];
	int		pipe_input;
	int		i;

	pipe_input = -1;
	i = 0;
	if (!list->next && is_builtin(list->cmd))
		execute_builtin(list, env);
	while (i < pid_count)
	{
		if (list->next && pipe(pip) == -1)
			error_message("pipe error", -1);
		pid[i] = fork();
		if (pid[i] == -1)
			error_message("fork error", -1);
		if (pid[i] == 0)
			child_process(list, pip, pipe_input, convert_env(env));
		handle_setup_close(list, pip, &pipe_input);
		close_files(list);

		list = list->next;
		i++;
	}
	wait_for_pids(pid, pid_count);
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