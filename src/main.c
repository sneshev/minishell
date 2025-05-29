/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/29 16:55:41 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <errno.h>

int	word_count(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			j++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (j);
}

bool	is_valid_input(char *line)
{
	char	**arguments;
	// char	**arg_type;
	int		wordcount;
	int		i;

	arguments = ft_split(line, ' ');
	if (!arguments)
		return (false);
	wordcount = word_count(line, ' ');
	i = 0;
	while (i < wordcount)
	{
		if (ft_strncmp(arguments[i], "<", 2) == 0)
			printf("is <\n");
		if (ft_strncmp(arguments[i], ">", 2) == 0)
			printf("is >\n");
		if (ft_strncmp(arguments[i], "|", 2) == 0)
			printf("is |\n");

		i++;
	}
	return (true);

}

void	minishell(char *line)
{
	(void)line;

	pid_t pid = fork();
    
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			printf("3");
			fflush(stdout);
			usleep(50000);
		}
		// exit(1);
	}
	else 
	{
		int status;
        while (waitpid(pid, &status, 0) == -1)
        {
            if (errno == EINTR)
                continue;
            perror("waitpid");
            break;
        }
		// exit(1);
	}
}

void	invalid_input(void)
{

}



int main(int argc, char *argv[])
{
	(void)argv;
	if (argc != 1)
		return (1);
    if (signal(SIGINT, handle_signals) == SIG_ERR)
    {
        perror("signal");
        return 1;
    }
	rl_catch_signals = 0;
	while(1)
	{
		char *line = readline("minishell$ ");
		g_signal = 0;
		printf("1"); fflush(NULL);
        if (!line) //ctrl + d
        {
            write(1, "exit\n", 5);
            break;
        }
		if (!(*line))
			write(1, "kur", 3);
		if (g_signal == SIGINT)
		{
			g_signal = -1;
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();  // Properly redraw the prompt
			free(line);
			continue;
		}
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			free(line);
			exit(1);
		}

		if (is_valid_input(line) == true)
			minishell(line);
		// else
		// 	invalid_input();
		free(line);

	}
	return (0);
}
