/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:59:59 by sneshev           #+#    #+#             */
/*   Updated: 2025/08/11 20:39:09 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "list.h"
#include <fcntl.h>

// if fd == -1 we will not pipe/close the pipe
// the computer will read this as empty input
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

int	count_cmd_args(char **tokens, int index)
{
	int	count;

	count = 0;
	while (tokens[index] && !is_pipe(tokens[index]))
	{
		if (is_redirect(tokens[index]) && tokens[index + 1])
			index += 2;
		else
		{
			count++;
			index++;
		}
	}
	return (count);
}

char	**get_cmd_args(char **tokens, int index)
{
	int		arg_count;
	char	**args;
	int		i;

	arg_count = count_cmd_args(tokens, index);
	if (arg_count < 1)
		return (NULL);
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens[index] && !is_pipe(tokens[index]))
	{
		if (is_redirect(tokens[index]) && tokens[index + 1])
			index += 2;
		else
		{
			args[i] = ft_strdup(tokens[index]);
			if (!args[i++])
				return (free_arr(args), NULL);
			(index)++;
		}
	}
	args[i] = NULL;
	return (args);
}

void	update_index(char **tokens, int *index)
{
	while (tokens[*index] && !is_pipe(tokens[*index]))
		(*index)++;
	if (tokens[*index] && is_pipe(tokens[*index]))
		(*index)++;
}

void	setup_node(t_list **node, char *cmd, char **args, int fd[2])
{
	(*node)->cmd = cmd;
	(*node)->args = args;
	(*node)->input = fd[0];
	(*node)->output = fd[1];
	(*node)->prev = NULL;
	(*node)->next = NULL;
}
