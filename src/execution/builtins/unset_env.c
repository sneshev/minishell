/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:08:42 by mmisumi           #+#    #+#             */
/*   Updated: 2025/09/10 13:05:39 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../execution.h"

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
		while (cur && is_matching_varname(cur->name, name) == false)
		{
			prev = cur;
			cur = cur->next;
		}
		if (cur && is_matching_varname(cur->name, name) == true)
			unset_var(env, cur, prev);
		i++;
		free(name);
	}
	return (0);
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
