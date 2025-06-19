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
	(void)envp;
	t_list	*new;
	int		index;

	new = NULL;
	index = 0;
	while (index < wordc)
	{
		new = new_node(tokens, &index);
		if (!new)
			return (free_list(list), NULL);
		add_node_back(list, new);
	}
	return (*list);
}

t_list	*get_list(char *line, char **envp)
{
	(void)envp;
	t_list	*list;
	char	**tokens;
	int		token_count;

	tokens = get_tokens(line);
	if (!tokens)
		return (NULL);
	token_count = count_tokens(line);
	list = NULL;
	create_list(&list, tokens, token_count, envp);
	if (!list)
		return (NULL);
	free_arr(tokens);
	return (list);
}
