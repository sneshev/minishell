#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"

# include <sys/types.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>

#define READ 0
#define WRITE 1

// temporary
void	print_arr(char **arr);
void	print_list(t_list *list);
void	print_files(t_file *file);

// utils
void	*xmalloc(size_t size);
void	free_arr(char **arr);
int		ft_strcmp(char *s1, char *s2);
int		word_count(char const *s);
bool	is_space(char c);

// tokens
char	**get_tokens(char *str, t_env *env);
int		count_tokens(char *str);
bool	is_pipe(char *str);
bool 	is_redirect(char *str);
bool 	is_builtin(char *str);

// list
t_list	*get_list(t_list *list, char *line, t_env *env);
void	free_env(t_env **env);
void	free_list(t_list **list);
void	free_file(t_file **file);

// env
t_env	*get_env(char **envp);
char	**arr_dup(char **arr);

// exits
void	exit_terminal(char *line);
void	exit_with_code(int exit_code);
void	error_message(char const *s, int exit_code);

//execute
void	execute(t_list *list, char **envp, int pid_count);
int		count_pids(t_list *list);

#endif