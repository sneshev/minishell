/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:36:03 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/24 16:41:40 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../execution.h"

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
