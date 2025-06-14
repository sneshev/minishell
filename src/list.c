/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:08:13 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/13 16:44:50 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_node(char *token, char **envp)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->arg = ft_strdup(token);
	if (!node->arg)
		return (NULL);
	node->arg_type = find_token_type(token);
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

t_list	*create_list(t_list **list, char **tokens, int wordc, char **envp)
{
	t_list	*new;
	int		index;

	new = NULL;
	index = 0;
	while (index < wordc)
	{
		new = new_node(tokens[index], envp);
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
	char	**tokens;
	int		token_count;

	tokens = get_tokens(line);
	if (!tokens)
		return (free_arr(tokens), NULL);
	token_count = count_tokens(line);
	list = NULL;
	create_list(&list, tokens, token_count, envp);
	if (!list)
		return (NULL);
	free_arr(tokens);
	return (list);
}
