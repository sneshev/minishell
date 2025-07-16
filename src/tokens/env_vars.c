#include "../minishell.h"
#include "tokens.h"

int find_varname_len(char *str)
{
	int count;

	if (!str)
		return (-1);
	count = 0;
	if (*str == '?')
		return (1);
	while (isalnum(str[count]) || str[count] == '_')
		count++;
	return (count);
}

int find_envvar_len(char *str, t_env *env)
{
	if (!env)
		return (0);
	if (*str == '?')
		return (ft_strlen(env->value));
	if (ft_strncmp(env->name, str, find_varname_len(str))
		|| env->name[find_varname_len(str)] != '=')
		return (find_envvar_len(str, env->next));
	return (ft_strlen(env->value));
}

char *find_envvar(char *str, t_env *env)
{
	if (!env)
		return (NULL);
	if (*str == '?')
		return (env->value);
	if (ft_strncmp(env->name, str, find_varname_len(str))
		|| env->name[find_varname_len(str)] != '=')
		return (find_envvar(str, env->next));
	return (env->value);
}

int add_env_variable(char *dest, char *src, int *j, t_env *env)
{
	char *envvar;
	int i;

	i = 0;
	envvar = find_envvar(src, env);
	while (envvar && envvar[i])
	{
		dest[*j] = envvar[i];
		(*j)++;
		i++;
	}
	return (i);
}