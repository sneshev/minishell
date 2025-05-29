/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/29 15:06:56 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	**arg_type;
	int		wordcount;
	int		i;

	arguments = ft_split(line, ' ');
	if (!arguments)
		return (false);
	wordcount = word_count(line, ' ');
	i = 0;
	while (i < wordcount)
	{
		if (arguments[i] == is_command())

		



		if (arguments[i][0] == '-')
		{
			printf("is -\n");
			if (arguments[i - 1] && arguments[i - 1] )
		}
		if (ft_strncmp(arguments[i], "<", 2) == 0)
			printf("is <\n");
		if (ft_strncmp(arguments[i], ">", 2) == 0)
			printf("is >\n");
		if (ft_strncmp(arguments[i], "|", 2) == 0)
			printf("is |\n");
		if ()
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
