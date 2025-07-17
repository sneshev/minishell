#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H


t_env	*create_env(t_env **env, char **envs);
void	add_env_node_back(t_env **env, t_env *current);
t_env	*new_env_node(char *name, char *value);
int		name_length(const char *s);
int		arr_length(char **arr);
char	*get_env_name(char *env);
char	*get_env_value(char *env);

#endif