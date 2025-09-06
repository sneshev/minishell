/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/09/06 16:26:27 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals/signals.h"
#include "history/history.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

#define UNINITIALIZED -2

char	*take_arg_nextline(char *arg)
{
	char		*line;
	static int	fd = UNINITIALIZED;

	if (fd == UNINITIALIZED)
	{
		if (access(arg, F_OK) != 0)
			return (write_err(arg, "No such file or directory"), NULL);
		else if (access(arg, R_OK) != 0)
			return (write_err(arg, "Permission denied"), NULL);
		fd = open(arg, O_RDONLY, 0400);
		if (fd == -1)
			return (NULL);
	}
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		exit(get_exit_code());
	}
	return (line);
}

char	*ft_readline(bool has_arg, char *arg)
{
	char	*line;

	if (has_arg)
		line = take_arg_nextline(arg);
	else if (isatty(STDIN_FILENO) == true)
	{
		line = readline("minishell$ ");
		ft_add_history(line, false);
	}
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			exit(get_exit_code());
	}
	return (line);
}

// void	minishell(char *envp[])
void	minishell(char **envp, bool has_arg, char *arg)
{
	char	*line;
	t_list	*list;
	t_env	*env;
	int		exitcode;

	env = get_env(envp);
	ft_read_history();
	while (1)
	{
		enable_signals();
		line = ft_readline(has_arg, arg);
		if (!line)
		{
			write(1, "exit\n", 5);
			exit_with_code(0, NULL, &env, NULL);
		}
		list = get_list(line, env);
		free(line);
		if (list)
		{
			exitcode = execute(list, &env);
			free_list(&list);
			set_exit_code(exitcode);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (argc == 1)
		minishell(envp, false, NULL);
	else
		minishell(envp, true, argv[1]);
	return (0);
}
