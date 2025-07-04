#include "minishell.h"

void exit_with_code(int exit_code)
{
	write_history(".minishell_history");
	write(1, "exit\n", 5);
	exit(exit_code % 256);
}

void exit_terminal(char *line)
{
	if (!line)
		exit_with_code(0);
	if (strncmp(line, "exit", 4) == 0)
	{
		line += 4;
		if (*line == '\0')
			exit_with_code(0);
		while(is_space(*line))
			line++;
		if (*line == '-' || *line == '+')
		{
			if (ft_isdigit(*(line + 1)))
				exit_with_code(ft_atoi(line));
			// else 
				// ; // exit error
		}
		else if (ft_isdigit(*line))
			exit_with_code(ft_atoi(line));
		//no good exit code 
	}
}