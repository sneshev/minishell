#include "../minishell.h"
#include "execution.h"

t_env	*create_var_node(char *var, t_env **env)
{
	char	*name;
	char	*value;
	t_env	*new;

	name = NULL;
	value = NULL;
	new = NULL;
	name = get_env_name(var);
	if (!name)
		return (NULL);
	value = get_env_value(var);
	if (!value)
		return (free(name), NULL);
	new = new_env_node(name, value);
	if (!new)
		return (free(name), free(value), NULL);
	add_env_node_back(env, new);
	return (new);
}

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
	environment[i] = NULL;
	return (environment);

}

bool	validate_export_syntax(char *cmd)
{
	int	i;

	i = 0;
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (false);
	i++;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd, "exit", 6) == 0)
		return (true);
	else
		return (false);
}

int	execute_builtin(t_list *list, t_env **env, char **environment)
{
	if (ft_strncmp(list->cmd, "echo", 5) == 0)
		return (execute_echo(list));
	else if (ft_strncmp(list->cmd, "cd", 3) == 0)
		return (execute_cd(list, *env));
	else if (ft_strncmp(list->cmd, "pwd", 4) == 0)
		return (execute_pwd());
	else if (ft_strncmp(list->cmd, "export", 7) == 0)
		return (execute_export(list, env));
	else if (ft_strncmp(list->cmd, "unset", 6) == 0)
		return (execute_unset(list, env));
	else if (ft_strncmp(list->cmd, "env", 4) == 0)
		return (execute_env(list, environment));
	else if (ft_strncmp(list->cmd, "exit", 6) == 0)
		return (execute_exit(list));
	return (0);
}
