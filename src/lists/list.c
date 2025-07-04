/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:08:13 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/04 16:01:59 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "list.h"

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

t_list	*new_node(int fd[2], char **tokens, int index)
{
	t_list	*node;
	char	**args;
	char	*cmd;
	t_file	*file;
	int		file_count;

	node = xmalloc(sizeof(t_list));
	args = get_cmd_args(tokens, index);
	if (!args)
		return (free(node), NULL);
	// print_arr(args);
	cmd = get_cmd(args[0]);
	if (!cmd)
		return (free(node), free_arr(args), NULL);
	// printf("cmd: %s\n", args[0]);
	file_count = count_redir_files(tokens, index);
	file = NULL;
	if (file_count > 0)
	{
		file = get_file_list(file, tokens, index, file_count);
		if (!file)
			return (free(node), free(args), free(cmd), NULL);
		// print_files(file);
	}
	create_files(fd, file);
	check_cmd_access(fd, cmd);
	node->cmd = cmd;
	node->args = args;
	node->input = fd[0];
	node->output = fd[1];
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	update_index(char **tokens, int *index)
{
	// printf("index before: %d  %s\n", *index, tokens[*index]);
	while(tokens[*index] && !is_pipe(tokens[*index]))
		(*index)++;
	// set to after the pipe
	if (tokens[*index] && is_pipe(tokens[*index]))
		(*index)++;
	// printf("index after: %d\n", *index); fflush(NULL);
}

t_list	*create_list(t_list *list, char **tokens, int wordc, char **envp)
{
	(void)envp;
	t_list	*new;
	int		index;
	int		fd[2];

	index = 0;
	// printf("wordcount: %d\n", wordc);
	while (index < wordc)
	{
		// printf("index: %d\n", index);
		new = new_node(fd, tokens, index);
		if (!new)
			return (free_list(&list), NULL);
		add_node_back(&list, new);
		update_index(tokens, &index);
		// printf("index: %d\n", index);
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
