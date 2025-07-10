#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/wait.h>
#define CHILD 0

// execution
char	*get_cmd(char *cmd);
int		execute(t_list *list, t_env **env, int pid_count);

// execute builtin
void	execute_echo(t_list *list);
void	execute_cd(t_list *list);
void	execute_pwd(void);
void	execute_export(t_list *list, t_env **env);
void	execute_unset(t_list *list, t_env **env);
void	execute_env(t_list *list, char **environment);
void	execute_exit(t_list *list);

// execute utils
char	**convert_env(t_env *env);
int		count_env_vars(t_env *env);
void	execute_builtin(t_list *list, t_env **env, char **environment);
int		is_builtin(char *cmd);

// free
void	free_env_node(t_env **prev_env);


// files
// int		replace_file(char *input, char *filename);
// int		append_to_file(char *input, char *filename);


#endif