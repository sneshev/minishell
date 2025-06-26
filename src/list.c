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

t_file	*get_file_list(t_file *file, char **tokens, int index)
{
	char	**files;

	files = get_redir_files(tokens, index);
	if (!files)
		return (NULL);
	file = create_file_list(file, files);
	if (!file)
		return (free_arr(files), NULL);
	return (file);
}

// int	validate_files(int fd[2], char **tokens, int index)
// {
// 	t_file	*file;
// 	char	**files;

// 	files = get_redir_files(tokens, index);
// 	if (!files)
// 		return (-1);
// 	file = NULL;
// 	file = put_redir_files(file, files);
// 	if (!file)
// 		return (free_arr(files), -1);
// 	if (create_files(fd, file) == -1)
// 		return (free(file), free_arr(files), -1);
// 	return (0);
// }

// t_list	*new_node(int fd[2], char **tokens, int *index)
// {
// 	t_list	*node;
// 	char	**args;

// 	node = malloc(sizeof(t_list));
// 	if (!node)
// 		return (NULL);
// 	args = get_cmd_args(tokens, index);
// 	if (!args)
// 		return (free(node), NULL);
// 	node->cmd = get_cmd(args[0]);
// 	if (!node->cmd)
// 		return (free_arr(args), free(node), NULL);
// 	node->args = args;
// 	node->input = fd[0];
// 	node->output = fd[1];
// 	return (free_arr(args), node);
// }

void	check_cmd_access(int fd[2], char *cmd)
{
	if (access(cmd, F_OK) == -1 || access(cmd, X_OK == -1))
	{
		fd[0] = -1;
		fd[1] = -1;
	}
}

t_list	*new_node(int fd[2], char **tokens, int *index)
{
	t_list	*node;
	char	**args;
	char	*cmd;
	t_file	*file;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	args = get_cmd_args(tokens, index);
	if (!args)
		return (free(node), NULL);
	cmd = get_cmd(args[0]);
	if (!cmd)
		return (free(node), free_arr(args), NULL);
	file = NULL;
	file = get_file_list(file, tokens, *index);
	if (!file)
		return (free(node), free(args), free(cmd), NULL);
	create_files(fd, file);
	check_cmd_access(fd, cmd);
	node->cmd = cmd;
	node->args = args;
	node->input = fd[0];
	node->output = fd[1];
	return (node);
}

t_list	*create_list(t_list *list, char **tokens, int wordc, char **envp)
{
	(void)envp;
	t_list	*new;
	int		index;
	int		fd[2];

	index = 0;
	while (index < wordc)
	{
		new = new_node(fd, tokens, &index);
		if (!new)
			return (free_list(&list), NULL);
		add_node_back(&list, new);
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
