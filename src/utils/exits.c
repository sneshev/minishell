#include "../minishell.h"
# include <readline/history.h>

void	error_message(char const *s, int exit_code)
{
	(void)exit_code;

	printf("%s\n", s);
	// exit (exit_code);
}

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
	if (ft_strncmp(line, "exit", 4) == 0)
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