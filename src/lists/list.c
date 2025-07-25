/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:08:13 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/25 15:32:21 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "list.h"
#include <fcntl.h>

void	setup_node(t_list **node, char *cmd, char **args, int fd[2])
{
	(*node)->cmd = cmd;
	(*node)->args = args;
	(*node)->input = fd[0];
	(*node)->output = fd[1];
	(*node)->prev = NULL;
	(*node)->next = NULL;
}

int	handle_files(char **tokens, int index, int fd[2], t_env *env)
{
	t_file	*file;
	int		file_count;

	file_count = count_redir_files(tokens, index);
	file = NULL;
	if (file_count > 0)
	{
		file = get_file_list(file, tokens, index, file_count);
		if (!file)
			return (-1);
	}
	if (create_files(fd, file, env) == HEREDOC_TERMINATED)
		return (free_file(&file), HEREDOC_TERMINATED);
	return (0);
}

t_list	*new_node(char **tokens, int index, t_env *env)
{
	t_list	*node;
	char	**args;
	char	*cmd;
	int		fd[2];

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	args = get_cmd_args(tokens, index);
	if (!args)
		return (free(node), NULL);
	cmd = NULL;
	if (is_builtin(args[0]))
		cmd = ft_strdup(args[0]);
	else
		cmd = get_cmd(env, args[0]);
	if (!cmd)
		cmd = NULL;
	if (handle_files(tokens, index, fd, env) == HEREDOC_TERMINATED)
		return (free(node), free_arr(args), free(cmd), NULL);
	setup_node(&node, cmd, args, fd);
	return (node);
}

void	update_index(char **tokens, int *index)
{
	while(tokens[*index] && !is_pipe(tokens[*index]))
		(*index)++;
	if (tokens[*index] && is_pipe(tokens[*index]))
		(*index)++;
}

t_list	*create_list(t_list *list, char **tokens, int wordc, t_env *env)
{
	t_list	*new;
	int		index;

	index = 0;
	while (index < wordc)
	{
		new = new_node(tokens, index, env);
		if (!new)
			return (free_list(&list), NULL);
		add_node_back(&list, new);
		update_index(tokens, &index);
	}
	return (list);
}

t_list	*get_list(t_list *list, char *line, t_env *env)
{
	char	**tokens;
	int		token_count;

	tokens = get_tokens(line, env);
	if (!tokens)
		return (NULL);
	if (!is_valid_syntax(tokens))
		return (free_arr(tokens), NULL);
	token_count = count_tokens(line, env);
	list = create_list(list, tokens, token_count, env);
	free_arr(tokens);
	return (list);
}
