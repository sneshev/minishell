/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:19:04 by mmisumi           #+#    #+#             */
/*   Updated: 2025/09/08 13:28:01 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

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
