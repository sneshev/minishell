/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:08:13 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/21 16:34:36 by mmisumi          ###   ########.fr       */
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

int	validate_files(int fd[2], char **tokens, int index)
{
	t_file	*file;
	char	**files;
	int		file_status;

	files = get_redir_files(tokens, index);
	if (!files)
		return (-1);
	file = NULL;
	file = put_redir_files(file, files);
	if (!file)
		return (free_arr(files), -1);
	file_status = create_files(fd, file);
	if (file_status == -1)
		return (free_arr(files), free_file(&file), -1);
	if (file_status == 1)
		return (free_arr(files), free_file(&file), 1);
	return (0);
}

t_list	*new_node(int fd[2], char **tokens, int *index)
{
	t_list	*node;
	char	**args;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	args = get_cmd_args(tokens, index);
	if (!args)
		return (free(node), NULL);
	node->cmd = get_cmd(args[0]);
	if (!node->cmd)
		return (free_arr(args), free(node), NULL);
	node->args = args;
	node->input = fd[0];
	node->output = fd[1];
	return (free_arr(args), node);
}

t_list	*create_list(t_list *list, char **tokens, int wordc, char **envp)
{
	(void)envp;
	t_list	*new;
	int		index;
	int		fd[2];
	int		file_status;

	index = 0;
	while (index < wordc)
	{
		file_status = validate_files(fd, tokens, index);
		if (file_status == -1)
			return (free_list(&list), NULL);
		else if (file_status == 0)
		{
			new = new_node(fd, tokens, &index);
			if (!new)
				return (free_list(&list), NULL);
			add_node_back(&list, new);
		}
		else if (file_status == 1)
			printf("no valid node\n");
	}
	return (list);
}

t_list	*get_list(t_list *list, char *line, char **envp)
{
	(void)envp;
	char	**tokens;
	int		token_count;

	tokens = get_tokens(line);
	if (!tokens)
		return (NULL);
	token_count = count_tokens(line);
	list = create_list(list, tokens, token_count, envp);
	free_arr(tokens);
	return (list);
}
