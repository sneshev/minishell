/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:05:09 by sneshev           #+#    #+#             */
/*   Updated: 2025/07/26 15:06:17 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "list.h"

void	free_file_node(t_file **prev_file)
{
	if (!prev_file || !*prev_file)
		return ;
	if ((*prev_file)->filename)
		free((*prev_file)->filename);
	free(*prev_file);
	*prev_file = NULL;
}

void	free_file(t_file **file)
{
	t_file	*temp;

	if (!file)
		return ;
	while (*file)
	{
		temp = *file;
		*file = (*file)->next;
		free_file_node(&temp);
	}
	*file = NULL;
}

void	free_list_node(t_list **prev_list)
{
	if (!prev_list || !*prev_list)
		return ;
	if ((*prev_list)->cmd)
		free((*prev_list)->cmd);
	if ((*prev_list)->args)
		free_arr((*prev_list)->args);
	free(*prev_list);
	*prev_list = NULL;
}

void	free_list(t_list **list)
{
	t_list	*temp;

	if (!list)
		return ;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free_list_node(&temp);
	}
	*list = NULL;
}
