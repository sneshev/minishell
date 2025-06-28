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
# include <fcntl.h>

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
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_list
{
	char			*cmd;
	char			**args;
	int				input;
	int				output;
	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

typedef enum e_redir_type {
	REDIR_IN,        // <
	REDIR_HEREDOC,   // <<
	REDIR_OUT,       // >
	REDIR_APPEND     // >>
}			t_redir_type;

typedef struct s_file
{
	t_redir_type	type;
	char			*filename;
	struct s_file	*next;
}	t_file;

// temporary
void	print_arr(char **arr);
void	print_list(t_list *list);
void	print_files(t_file *file);

// main
int		main(int argc, char *argv[], char *envp[]);
void	minishell(char **envp);
bool    validate_syntax(char **tokens);

// list
t_list	*get_list(t_list *list, char *line, char **envp);
t_list	*create_list(t_list *list, char **tokens, int wordc, char **envp);
t_list	*new_node(int fd[2], char **tokens, int index);
void	add_node_back(t_list **list, t_list *current);
void	update_index(char **tokens, int *index);

// list utils
void		create_files(int fd[2], t_file *file);
int			handle_heredoc(t_file **file);
t_file		*create_file_list(t_file *file, char **files);
t_file		*get_file_list(t_file *file, char **tokens, int index, int file_count);
t_file		*new_file_node(char *redir_type, char *filename);
char		**get_cmd_args(char **tokens, int index);
char		**get_redir_files(char **tokens, int index, int file_count);
int			count_redir_files(char **tokens, int index);
int			count_cmd_args(char **tokens, int index);
void		add_filenode_back(t_file **file, t_file *current);
void		check_cmd_access(int fd[2], char *cmd);

// list free
void	free_env(t_env **env);
void	free_env_node(t_env **prev_env);
void	free_list(t_list **list);
void	free_list_node(t_list **prev_list);
void	free_file(t_file **file);
void	free_file_node(t_file **prev_file);

// tokens
char	**get_tokens(char *str);
void	 add_token(char **arr, int index,char *str);
int		count_tokens(char *str);
int		find_token_len(char *str);
bool	 is_space(char c);
bool	is_quote(char c);

// token type
int		find_token_type(char *arg);
bool	is_pipe(char *str);
bool 	is_redirect(char *str);
bool 	is_builtin(char *str);//some of these are also 2 (recognized by access) so what are they?;

// utils
void	error_message(char const *s, int exit_code);
void	free_arr(char **arr);
int		word_count(char const *s);
void	malloc_fail(char *s, int exitcode);

// get command
char	*get_cmd(char *cmd);
char	**get_paths(char *cmd);

// env
t_env	*get_env(char **envp);
t_env	*create_env(t_env **env, char **envs);
void	add_env_node_back(t_env **env, t_env *current);
t_env	*new_env_node(char *name, char *value);

//
int		name_length(const char *s);
int		arr_length(char **arr);
char	*get_env_name(char *env);
char	*get_env_value(char *env);
char	**arr_dup(char **arr);

#endif