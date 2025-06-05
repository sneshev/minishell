/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:01:33 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/05 12:28:42 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
}
//i didnt try to test this at all yet...
void	execute_command(t_node **node)
{
	char	*cmd;
	int		flagc;
	char	**flags;
	int		pid;

	pid = fork();
	if (pid == -1)
		error_message("fork error\n", -1);
	
	cmd = get_cmd((*node)->arg, (*node)->envp);
	if (!cmd)
		error_message("malloc error\n", -1);
	printf("cmd: %s\n", cmd);
	(*node)->arg = cmd;
	flagc = flag_count(node);
	printf("flagc: %d\n", flagc);
	flags = get_flags(flagc, node);
	print_arr(flags);//!!SOMETHING GOES WRONG HERE!!
	if (!flags)
	{
		free(cmd);
		error_message("malloc error\n", -1);
	}
	if (access(cmd, X_OK) == -1)
		error_message("access execute error\n", 126);
	execve(flags[0], flags, (*node)->envp);//if execve is succesfull it will terminate and never get too the error_message
	error_message("execve error\n", 127);//this means execve error
}

void	print_node(t_node *node)
{
	printf("index: %d\n", node->index);
	printf("arg: %s\n", node->arg);
	print_type(node->arg_type);
	printf("-----------------------\n");
}

int	execute(t_node **list)
{
	t_node	*temp;

	temp = *list;
	while (temp)
	{
		if (temp->arg_type == BUILTIN)
		{
			print_node(temp);
		// 	// execute_builtin(&temp);
		}
		else if (temp->arg_type == COMMAND)
		{
			print_node(temp);
			execute_command(&temp);
		}
		else if (temp->arg_type == PIPE)
		{
			print_node(temp);
		// 	// execute_pipe();
		}
		else if (temp->arg_type == REDIRECTION)
		{
			print_node(temp);
		// 	// execute_direction();
		}
		temp = temp->next;
	}
	return (0);
}
