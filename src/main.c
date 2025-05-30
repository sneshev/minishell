/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/30 18:15:40 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define COMMAND 1
#define FLAG 2
#define REDIRECTION 3
#define PIPE 4
#define STRING 5

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

bool	is_valid_input(char *line)
{
	char	**arguments;
	int		*arg_type;
	int		wordcount;
	int		i;

	arguments = ft_split(line, ' ');
	if (!arguments)
		return (false);
	arg_type = malloc(word_count);
	if (!arg_type)
		return (false);
	wordcount = word_count(line);
	i = 0;
	while (i < wordcount)
	{
		if (is_command(arguments[i]))
			arg_type[i] = COMMAND;
		if (arguments[i] == is_flag())
			arg_type[i] = FLAG;
		if (is_pipe(arguments[i]))
			arg_type[i] = PIPE;
		if (is_redirect(arguments[i]))
			arg_type = REDIRECTION;
		i++;
	}
	return (true);

}

void	minishell(char *line)
{
	(void)line;
}

void	invalid_input(void)
{

}
int main(int argc, char *argv[])
{
	(void)argv;
	if (argc != 1)
		return (1);
	while(1)
	{
		char *line = readline("minishell$ ");
		if (ft_strncmp(line, "exit", 5) == 0)
			exit(1);

		if (is_valid_input(line) == true)
			minishell(line);
		// else
		// 	invalid_input();

	}
	return (0);
}
