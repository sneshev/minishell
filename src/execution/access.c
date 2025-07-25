/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:19:04 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/25 15:11:42 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

// int	check_access(char *cmd)
// {
// 	if (access(cmd, F_OK) == 0)
// 	{
// 		if (is_directory(cmd) == true)
// 			return (write_err(cmd, "is a directory"), 126);
// 		if (access(cmd, X_OK) == -1)
// 			return (write_err(cmd, "Permission denied"), 126);
// 		return (0);
// 	}
// 	write_err(cmd, "command not found");
// 	return (127);
// }

// int	check_invalid_file_cmd(t_list *list, t_env *env)
// {
// 	if (list->input == -1 && list->output == -1)
// 		return (1);
// 	if (is_builtin(list->cmd))
// 		return (0);
// 	if (list->cmd[0] == '/' || list->cmd[0] == '.')
// 		return (check_access(list->cmd));
// 	if (get_cmd(env, list->cmd) == NULL)
// 		return (write_err(list->cmd, "command not found"), 127);
// 	return (check_access(list->cmd));
// }
// int	check_invalid_file_cmd(t_list *list, t_env *env)
// {
// 	if (list->input == -1 && list->output == -1)
// 		return (1);
// 	if (is_builtin(list->cmd))
// 		return (0);
// 	if (ft_strcmp)
// 		return (check_access(list->cmd));
	
// 	//we still check this cause if its neither a builtin or cmd we still strdup cause we need to node
// 	if (get_cmd(env, list->cmd) == NULL)
// 		return (write_err(list->cmd, "command not found"), 127);
// 	return (check_access(list->cmd));
// }

int	check_invalid_file_cmd(t_list *list, t_env *env)
{
	(void)env;
	if (list->input == -1 && list->output == -1)
		return (1);
	if (is_builtin(list->cmd))
		return (0);
	if (!list->cmd)
		return (127);
	if (is_directory(list->cmd) == true)
		return (126);
	if (access(list->cmd, X_OK) == -1)
		return (126);
	return (0);
}