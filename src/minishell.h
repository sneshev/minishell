#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>

#define BUILTIN 1
#define COMMAND 2
#define REDIRECTION 3
#define PIPE 4
#define UNDEFINED 5
#define SQUOTE 6
#define DQUOTE 7

#define	TRUE 0
#define READ 0
#define WRITE 1

typedef struct	s_env
{
	char	*name;
	char	*value;
	char	*next;
}				t_env;


// typedef struct s_list
// {
// 	char	*cmd;
// 	char	**args;
// 	int		pipe[2];
// 	int		redirection;
// 	t_env	env;
// };

typedef struct	s_list
{
	char			*arg;
	int				arg_type;
	int				pipe[2];
	char			**envp;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;


//temporary
void	print_arr(char **arr);
void	print_type(int type);
void	print_list(t_list *list);
void	print_line(t_list *list);

//	get_args
bool	is_space(char c);
int		find_arg_len(char *str);
int		count_args(char *str);
char	**get_args(char *str);

//	path
char	**get_paths(char *cmd);
char	*get_cmd(char *cmd);

//	arg_types
bool	is_builtin(char *str);
int		find_arg_type(char *arg);
bool	is_command(char *str);
bool	is_redirect(char *str);
bool	is_pipe(char *str);

//	list
void	free_node(t_list **node);
void	free_list(t_list **list);
t_list	*new_node(char *arg, char **envp);
void	add_node_back(t_list **list, t_list *current);
t_list	*create_list(t_list **list, char **args, int wordc, char **envp);
t_list	*get_list(char *line, char **envp);

//	signals
extern volatile sig_atomic_t	g_signal;
void	enable_signals(void);
void	receive_SIGINT();

//	utils
int		word_count(char const *s);
void	free_arr(char **arr);
void	error_message(char const *s, int exit_code);

//execute
int		execute(t_list **list);
void	execute_command(t_list **list);
void	child_process(t_list **list, int *new_pipe, t_list *prev);


//execute utils
int		flag_count(t_list **list);
char	**get_flags(int flagc, t_list **list);
char	**put_flags(t_list **list);

#endif