/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/31 16:42:28 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_count(char const *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0')
		{
			j++;
			while (s[i] != ' ' && s[i] != '\0')
				i++;
		}
	}
	return (j);
}

bool	is_valid_input(char *line, char **envp)
{
	t_node	*list;
	char	**args;
	int		wordc;

	args = ft_split(line, ' ');
	if (!args)
		return (false);//should we specify its a malloc error?
	wordc = word_count(line);
	list = NULL;
	create_list(&list, args, wordc, envp);
	free_array(args);
	if (!list)
		return (false);
	print_list(list);
	free_list(&list);
	return (true);
}

void	minishell(char *line)
{
	(void)line;
}

void	invalid_input(void)
{

}

int main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (argc != 1)
		return (1);
	enable_signals();
	while(1)
	{
		char *line = readline("minishell$ ");
		if (!line || ft_strncmp(line, "exit", 5) == 0)
		{
			write(1, "exit\n", 5);
			exit(1);
		}
		if (g_signal == SIGINT)
			receive_SIGINT();
		if (is_valid_input(line, envp) == true)
			minishell(line);
		// else
		// 	invalid_input();
	}
	return (0);
}
