/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:59:57 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/10 13:13:40 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag_count(t_list **list)
{
	t_list	*temp;
	int		flagc;

	flagc = 0;
	temp = *list;
	while (temp && temp->arg_type != REDIRECTION && temp->arg_type != PIPE)
	{
		flagc++;
		temp = temp->next;
	}
	printf("flagc: %d\n", flagc);
	return (flagc);
}

//this will returns flags, but the list pointer is still pointing to the last flag
char	**get_flags(int flagc, t_list **list)
{
	char	**flags;
	int		i;

	printf("listpointer: %s\n", (*list)->arg);
	//we will also put the command in here thats why
	flags = malloc(sizeof(char *) * (flagc  + 1));
	if (!flags)
		return (NULL);
	i = 0;
	while (i < flagc - 1)
	{
		flags[i] = ft_strdup((*list)->arg);
		if (!flags[i])
			return (free_arr(flags), error_message("malloc error", 1), NULL);
		*list = (*list)->next;
		i++;

	}
	//now our pointer is on the last command
	flags[i] = ft_strdup((*list)->arg);
	flags[flagc] = NULL;
	return (flags);
}

char	**put_flags(t_list **list)
{
	char	*cmd;
	int		flagc;
	char	**flags;

	cmd = get_cmd((*list)->arg);
	if (!cmd)
		error_message("malloc error", 1);
	(*list)->arg = cmd;
	flagc = flag_count(list);
	flags = get_flags(flagc, list);
	if (!flags)
	{
		free(cmd);
		error_message("malloc error", 1);
	}
	if (access(cmd, X_OK) == -1)
		error_message("access execute error", 126);
	return (flags);
}
