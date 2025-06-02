/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:33 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/02 18:59:52 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char *arg, t_node **list)
{
	char	*cmd;
	int		flagc;
	char	**flags;

	cmd = get_cmd(arg, (*list)->envp);
	if (!cmd)
		return (0);
	flagc = flag_count(list);
	flags = get_flags(list);
	if (!flags)
		return (free(cmd), 0);
	if (execve(cmd, flags, (*list)->envp) == -1)
		return (error_message());
}

int	execute(t_node **list)
{
	char	*arg;
	t_node	*temp;
	int		i;

	temp = *list;
	i = 0;
	while (temp)
	{
		if (temp->arg_type == BUILTIN)
			execute_builtin();
		else if (temp->arg_type == COMMAND)
			execute_command();
		else if (temp->arg_type == PIPE)
			execute_pipe();
		else if (temp->arg_type == REDIRECTION)
			execute_direction();
		while (temp->next && i < temp->index)
			temp = temp->next;
	}
	return (0);
}
