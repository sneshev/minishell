/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:08:13 by mmisumi           #+#    #+#             */
/*   Updated: 2025/05/31 16:39:29 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_node *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("%d	list->line: %s\n", i, list->arg);
		printf("%d	list->arg_type: %d\n", i, list->arg_type);
		printf("-----------------------\n");
		list = list->next;
		i++;
	}
}

void	free_node(t_node **node_ptr)
{
	t_node	*node;

	if (!node_ptr)
		return ;
	node = *node_ptr;
	if (node)
	{
		if (node->arg)
			free(node->arg);
		// if (node->next)
			// free(node->next);
		free(node);
		node = NULL;
	}
}

void	free_list(t_node **list)
{
	t_node	*temp;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free_node(&temp);
	}
	*list = NULL;
}

t_node	*new_node(char *arg, char **envp)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->arg = ft_strdup(arg);
	if (!node->arg)
		return (NULL);
	node->arg_type = find_arg_type(arg, envp);
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
}

t_node	*create_list(t_node **list, char **args, int wordc, char **envp)
{
	t_node	*new;
	int		index;

	new = NULL;
	index = 0;
	while (index < wordc)
	{
		new = new_node(args[index], envp);
		if (!new)
			return (free_list(list), NULL);
		add_node_back(list, new);
		index++;
	}
	return (*list);
}
