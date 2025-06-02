/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:59:57 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/02 16:00:37 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag_count(t_node **list)
{
	t_node	*temp;
	int		flagc;

	temp = *list;
	while (temp)
	{
		if (temp->arg == UNDEFINED)
		{
			flagc++;
			temp = temp->next;
		}
		else
			break ;
	}
	return (flagc);
}

bool	get_flags(t_node **list)
{
	t_node	*temp;
	char	**flags;
	int		flagc;
	int		i;

	flagc = flag_count(list);
	flags = malloc(sizeof(char *) * (flagc + 1));
	if (!flags)
		return (false);
	i = 0;
	while (i <= flagc)
	{
		if (i == 0)
			flags[i] = temp->prev->arg;
		else
			flags[i] = temp->arg;
		i++;
	}
	return (*flags);
}