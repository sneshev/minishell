#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
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

// temporary
void	print_arr(char **arr);
void	print_list(t_list *list);
void	print_files(t_file *file);

// main
int		main(int argc, char *argv[], char *envp[]);
void	minishell(char **envp);
bool    validate_syntax(char **tokens);

// exits
void exit_terminal(char *line);
void exit_with_code(int exit_code);



// list
t_list	*get_list(t_list *list, char *line, char **envp);
void	free_env(t_env **env);
void	free_list(t_list **list);
void	free_file(t_file **file);

// tokens
char	**get_tokens(char *str);
void	 add_token(char **arr, int index,char *str);
int		count_tokens(char *str);
int		find_token_len(char *str);
bool	is_quote(char c);

// token type
bool	is_pipe(char *str);
bool 	is_redirect(char *str);
bool 	is_builtin(char *str);

// utils
bool	is_space(char c);
void	error_message(char const *s, int exit_code);
void	free_arr(char **arr);
int		word_count(char const *s);
void	*xmalloc(size_t size);
int		ft_strcmp(char *s1, char *s2);


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