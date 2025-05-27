/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:08:45 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/27 16:31:00 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("%s\n", line);
	}
	return (0);
}