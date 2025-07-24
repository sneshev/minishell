/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:08:42 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/24 16:33:34 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

//im not sure if i need to pass cur and prev as double pointers to also delete original node
void	unset_var(t_env **env, t_env *cur, t_env *prev)
{
	t_env *temp;

	if (prev)
		prev->next = cur->next;
	else
		*env = cur->next;
	temp = cur;
	free_env_node(&temp);
}

bool	is_matching_varname(char *var, char *name)
{
	int	namelen;

	namelen = ft_strlen(name);
	if (ft_strcmp(var, name) == 0)
		return (true);
	if (ft_strncmp(var, name, namelen) == 0 && var[namelen] == '=')
		return (true);
	return (false);
}

int	execute_unset(t_list *list, t_env **env)
{
	int		i;
	t_env	*cur;
	t_env	*prev;
	char	*name;

	i = 1;
	while (list->args[i])
	{
		cur = *env;
		prev = NULL;
		name = get_env_name(list->args[i]);
		if (!name)
			return (1);
		while (cur)
		{
			if (is_matching_varname(cur->name, name) == true)
			{
				unset_var(env, cur, prev);
				break ;
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
		free(name);
	}
	return (0);
}

bool	is_env_var(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

void	print_env(char **environment)
{
	int	i;

	i = 0;
	while (environment[i])
	{
		if (is_env_var(environment[i]) == true)
			printf("%s\n", environment[i]);
		i++;
	}
}

int	execute_env(t_list *list, char **environment)
{
	if (list->args[1])
		return (write_err("env", "too many arguments"), -1);
	print_env(environment);
	return (0);
}