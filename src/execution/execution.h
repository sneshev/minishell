#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/wait.h>

// execution
char	*get_cmd(char *cmd);
void	execute(t_list *list, t_env *env, int pid_count);

// execute builtin
void	execute_echo(t_list *list);
void	execute_cd(t_list *list);
void	execute_pwd(t_list *list);
void	execute_export(t_list *list, t_env *env);
void	execute_unset(t_list *list, t_env *env);
void	execute_env(t_list *list, t_env *env);
void	execute_exit(t_list *list);

// files
// int		replace_file(char *input, char *filename);
// int		append_to_file(char *input, char *filename);


#endif