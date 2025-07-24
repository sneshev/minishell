/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:08:42 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/24 15:26:26 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

//not working correctly yet
int	execute_unset(t_list *list, t_env **env)
{
	t_env	*cur;
	t_env	*prev;
	t_env	*temp;
	char	*name;
	int		i;

	i = 1;
	while (list->args[i])
	{
		cur = *env;
		prev = NULL;
		name = get_env_name(list->args[i]);
		if (!name)
			return (-1);
		while (cur)
		{
			if (ft_strncmp(cur->name, name, ft_strlen(name)) == 0
			&& cur->name[ft_strlen(name)] == '=')
			{
				if (prev)
				{
					prev->next = cur->next;
					temp = cur;
					cur = cur->next;
				}
				else
				{
					*env = cur->next;
					temp = cur;
					cur = *env;
				}
				free_env_node(&temp);
				break ;
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
	free(name);
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