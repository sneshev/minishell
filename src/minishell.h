#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

#define BUILTIN 1
#define COMMAND 2
#define REDIRECTION 3
#define PIPE 4
#define UNDEFINED 5
#define SQUOTE 6
#define DQUOTE 7

#define READ 0
#define WRITE 1

typedef struct	s_node
{
	char			*arg;
	int				arg_type;
	int				index;
	char			**envp;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;


//temporary
void	print_type(int type);
void	print_list(t_node *list);

//	input
bool	is_valid_input(char *line, char **envp);
// void	handle_invalid_input(void);

//	get_args
bool	is_space(char c);
int		find_arg_len(char *str);
int		count_args(char *str);
char	**get_args(char *str);

//	path
char	*get_env(char **envp);
char	**get_path(char *path, char *cmd);
char	*get_cmd(char *str, char **envp);

//	arg_types
bool	is_builtin(char *str);
int		find_arg_type(char *arg, char **envp);
bool	is_command(char *str, char **envp);
bool	is_redirect(char *str);
bool	is_pipe(char *str);

//	list
void	print_list(t_node *list);
void	free_node(t_node **node);
void	free_list(t_node **list);
t_node	*new_node(char *arg, int index, char **envp);
void	add_node_back(t_node **list, t_node *current);
t_node	*create_list(t_node **list, char **args, int wordc, char **envp);

//	signals
extern volatile sig_atomic_t	g_signal;
void	enable_signals(void);
void	receive_SIGINT();

//	utils
int		word_count(char const *s);
void	free_arr(char **arr);
void	error_message(char const *s, int exit_code);

//execute
void	execute_command(t_node **node);
int		execute(t_node **list);

//execute utils
char	**get_flags(int flagc, t_node **node);
int		flag_count(t_node **node);

#endif