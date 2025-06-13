/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:08:13 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/13 12:40:46 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_node(char *arg, char **envp)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->arg = ft_strdup(arg);
	if (!node->arg)
		return (NULL);
	node->arg_type = find_arg_type(arg);
	node->pipe[READ] = -1;
	node->pipe[WRITE] = -1;
	node->envp = envp;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	add_node_back(t_list **list, t_list *current)
{
	t_list	*temp;

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

t_list	*create_list(t_list **list, char **args, int wordc, char **envp)
{
	t_list	*new;
	int		index;

	new = NULL;
	index = 0;
	while (index < wordc)
	{
		new = new_node(args[index], envp);
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

t_list	*get_list(char *line, char **envp)
{
	t_list	*list;
	char	**args;
	int		arg_count;

	args = get_args(line);
	if (!args)
		return (free_arr(args), NULL);
	arg_count = count_args(line);
	list = NULL;
	create_list(&list, args, arg_count, envp);
	if (!list)
		return (NULL);
	free_arr(args);
	return (list);
}
