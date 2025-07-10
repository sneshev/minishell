#include "../minishell.h"
#include "execution.h"


int	count_env_vars(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**convert_env(t_env *env)
{
	int		vars;
	char	**environment;
	int		i;

	if (!env)
		return (NULL);
	vars = count_env_vars(env);
	environment = malloc(sizeof(char *) * (vars + 1));
	if (!environment)
		return (NULL);
	i = 0;
	while (env)
	{
		environment[i] = ft_strjoin(env->name, env->value);
		if (!environment[i])
			return (free_arr(environment), NULL);
		i++;
		env = env->next;
	}
	return (environment);

}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (2);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (2);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (2);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 6) == 0)
		return (2);
	else
		return (-1);
}

void	execute_builtin(t_list *list, t_env **env, char **environment)
{
	if (ft_strncmp(list->cmd, "echo", 5) == 0)
		execute_echo(list);
	else if (ft_strncmp(list->cmd, "cd", 3) == 0)
		execute_cd(list);
	else if (ft_strncmp(list->cmd, "pwd", 4) == 0)
		execute_pwd();
	else if (ft_strncmp(list->cmd, "export", 7) == 0)
		execute_export(list, env);
	else if (ft_strncmp(list->cmd, "unset", 6) == 0)
		execute_unset(list, env);
	else if (ft_strncmp(list->cmd, "env", 4) == 0)
		execute_env(list, environment);
	else if (ft_strncmp(list->cmd, "exit", 6) == 0)
		execute_exit(list);
}