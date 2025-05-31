#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>

#define BUILTIN 1
#define COMMAND 2
#define REDIRECTION 3
#define PIPE 4
#define STRING 5
#define FLAG 6

typedef struct	s_node
{
	char			*arg;
	int				arg_type;
	struct s_node	*next;
}					t_node;

int		word_count(char const *s);
bool	is_valid_input(char *line, char **envp);
void	minishell(char *line);

void	free_array(char **arr);
char	*get_env(char **envp);
char	**get_path(char *path, char *cmd);

//	arg_types
bool	is_builtin(char *str);
int		find_arg_type(char *arg, char **envp);
bool	is_command(char *str, char **envp);
bool	is_redirect(char *str);
bool	is_pipe(char *str);
bool	is_flag(char *str);

//list
void	print_list(t_node **list);
void	free_node(t_node **node);
void	free_list(t_node **list);
t_node	*new_node(char *arg, char **envp);
void	add_node_back(t_node **list, t_node *current);
t_node	*create_list(t_node **list, char **args, int wordc, char **envp);

#endif