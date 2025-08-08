/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:20:34 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/25 13:35:10 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/wait.h>
# define CHILD 0

//execute
int		execute(t_list *list, t_env **env);

void	child_process(t_list *list, int pip[3], t_env **env, char **environment);
//access
int		check_invalid_file_cmd(t_list *list, t_env *env);

//builtin
bool	is_builtin(char *cmd);
int		execute_builtin(t_list *list, t_env **env, char **environment);
int		execute_builtin_parent(t_list *list, t_env **env, char **environment);

//execute biultin
int		execute_pwd(void);
int		execute_cd(t_list *list, t_env *env);
int		execute_echo(t_list *list);

//waitpid
int		count_pids(t_list *list);
int		wait_for_pids(pid_t *pid, int pid_count);

//utils
bool	is_newline_flag(char *arg);
int		ft_envlen(t_env *env);
void	close_files(t_list *list);

//export
int		execute_export(t_list *list, t_env **env);

//export utils
void	write_export_err(char *s);
bool	validate_export_syntax(char *cmd);
int		existing_name(t_env *env, char *name);
t_env	*get_lowest_node(t_env *env);
t_env	*get_next_lowest_node(t_env *env, t_env *lowest);

//env
int		execute_env(t_list *list, char **environment);
int		execute_unset(t_list *list, t_env **env);

//env utils
bool	is_env_var(char *s);
bool	is_matching_varname(char *var, char *name);
void	unset_var(t_env **env, t_env *cur, t_env *prev);

//convert env
char	**convert_env(t_env *env);

// execution
char	*get_cmd(t_env *env, char *cmd);
int		execute(t_list *list, t_env **env);

//utils
bool	is_newline_flag(char *arg);

// execute builtin
void	print_env(char **environment);
bool	is_env_var(char *s);

int		execute_echo(t_list *list);
int		execute_cd(t_list *list, t_env *env);
int		execute_pwd(void);
int		execute_export(t_list *list, t_env **env);
int		execute_unset(t_list *list, t_env **env);
int		execute_env(t_list *list, char **environment);
int		execute_exit(
			t_list *list, t_env **env_ptr, char **environment, bool in_pipe);

// execute utils
char	**convert_env(t_env *env);
int		count_env_vars(t_env *env);

// free
void	free_env_node(t_env **prev_env);

// env
char	*get_env_value(char *env);
char	*get_env_name(char *env);
void	add_env_node_back(t_env **env, t_env *current);
t_env	*new_env_node(char *name, char *value);

#endif