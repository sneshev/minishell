/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:50:47 by sneshev           #+#    #+#             */
/*   Updated: 2025/09/08 13:29:13 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "signals/signals.h"
# include "structs.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# define READ 0
# define WRITE 1

// utils
void	write_err(char *keyword, char *message);
void	free_arr(char **arr);
int		ft_strcmp(char *s1, char *s2);
int		word_count(char const *s);
bool	is_space(char c);
void	print_arr(char **arr);
void	perror_message(char *s);
int		count_strings(char **arr, bool count_empty);
long	ft_atol(const char *nptr);

// tokens
char	**get_tokens(char *str, t_env *env, int total_tokens);
bool	is_valid_syntax(char **tokens);
int		count_tokens(char *str, t_env *env);
bool	is_pipe(char *str);
bool	is_redirect(char *str);
bool	is_directory(const char *path);

// list
t_list	*get_list(char *line, t_env *env);
void	free_env(t_env **env);
void	free_list(t_list **list);
void	free_file(t_file **file);

// env
t_env	*get_env(char **envp);
char	**arr_dup(char **arr);

// exit_codes
void	set_exit_code(int new_code);
int		get_exit_code(void);

// history
int		ft_read_history(void);
int		ft_add_history(char *line, bool close_fd);

// exits
void	error_message(char const *s, int exit_code);
void	exit_with_code(
			int exit_code, t_list **list_ptr,
			t_env **env_ptr, char **environment);

// execute
int		execute(t_list *list, t_env **env);
int		count_pids(t_list *list);
bool	is_builtin(char *cmd);

#endif