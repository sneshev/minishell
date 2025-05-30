#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>


int		word_count(char const *s);
bool	is_valid_input(char *line);
void	minishell(char *line);
int		main(int argc, char *argv[]);

char	*get_env(char **envp);
char	**get_path(char *path, char *cmd);

//	arg_types
bool	is_command(char *str, char **envp);
bool	is_redirect(char *str);
bool	is_pipe(char *str);


#endif