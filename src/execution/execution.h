#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/wait.h>
#define CHILD 0

// execution
char	*get_cmd(char *cmd);
int		execute(t_list *list, t_env **env);

// execute builtin
int	execute_echo(t_list *list);
int	execute_cd(t_list *list);
int	execute_pwd(void);
int	execute_export(t_list *list, t_env **env);
int	execute_unset(t_list *list, t_env **env);
int	execute_env(t_list *list, char **environment);
int	execute_exit(t_list *list);

// execute utils
char	**convert_env(t_env *env);
int		count_env_vars(t_env *env);
void	execute_builtin(t_list *list, t_env **env, char **environment);
bool	is_builtin(char *cmd);
t_env	*create_var_node(char *var, t_env **env);

// free
void	free_env_node(t_env **prev_env);

// env
char	*get_env_value(char *env);
char	*get_env_name(char *env);
void	add_env_node_back(t_env **env, t_env *current);
t_env	*new_env_node(char *name, char *value);


// files
// int		replace_file(char *input, char *filename);
// int		append_to_file(char *input, char *filename);


#endif