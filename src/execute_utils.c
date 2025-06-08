/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:59:57 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/05 12:29:55 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag_count(t_list **list)
{
	t_list	*temp;
	int		flagc;

	flagc = 0;
	temp = (*list)->next;
	while (temp && temp->arg_type != REDIRECTION && temp->arg_type != PIPE)
	{
		flagc++;
		temp = temp->next;
	}
	return (flagc);
}

//this will returns flags, but the list pointer is still pointing to the last flag
char	**get_flags(int flagc, t_list **list)
{
	char	**flags;
	int		i;

	//we will also put the command in here thats why
	flags = malloc(sizeof(char *) * (flagc + 1 + 1));
	if (!flags)
		return (NULL);
	i = 0;
	while (i < flagc)
	{
		flags[i] = ft_strdup((*list)->arg);
		if (!flags[i])
			return (free_arr(flags), error_message("malloc error\n", -1), NULL);
		*list = (*list)->next;
		i++;
	}
	flags[i] = NULL;
	return (flags);
}

