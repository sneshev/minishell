/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:08:13 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/04 16:26:23 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node(char *arg, int index, char **envp)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->arg = ft_strdup(arg);
	if (!node->arg)
		return (NULL);
	node->arg_type = find_arg_type(arg, envp);
	node->index = index;
	node->envp = envp;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	add_node_back(t_node **list, t_node *current)
{
	t_node	*temp;

	if (*list == NULL)
	{
		*list = current;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = current;
	current->prev = temp;
}

t_node	*create_list(t_node **list, char **args, int wordc, char **envp)
{
	t_node	*new;
	int		index;

	new = NULL;
	index = 0;
	while (index < wordc)
	{
		new = new_node(args[index], index + 1, envp);
		if (!new)
			return (free_list(list), NULL);
		if (*list == NULL)
			*list = new;
		else
			add_node_back(list, new);
		index++;
	}
	return (*list);
}
