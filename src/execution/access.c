/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:19:04 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/24 15:19:35 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

int	check_access(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == -1)
				return (write_err(cmd, "Permission denied"), 126);
			return (0);
		}
		write_err(cmd, "No such file or directory");
		return (127);
	}
	else
	{
		if (access(cmd, F_OK) == 0)
		{
			//check for is a directory
			if (access(cmd, X_OK) == -1)
				return (write_err(cmd, "Permission denied"), 126);
			return (0);
		}
		write_err(cmd, "command not found");
		return (127);
	}
}

int	check_invalid_file_cmd(t_list *list)
{
	if (list->input == -1 && list->output == -1)
		return (1);
	if (is_builtin(list->cmd))
		return (0);
	return (check_access(list->cmd));
}
