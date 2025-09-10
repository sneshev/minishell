/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:55:37 by mmisumi           #+#    #+#             */
/*   Updated: 2025/09/10 15:56:15 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../execution.h"

bool	is_newline_flag(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	update_pwd(t_env *env, char *name, char **pwd)
{
	int	i;
	int	index;

	index = existing_name(env, name);
	if (index == -1)
		return (1);
	i = 0;
	while (i < index)
	{
		env = env->next;
		i++;
	}
	if (env->value)
		free(env->value);
	env->value = *pwd;
	return (0);
}

void	cd_error(char *new_dir)
{
	if (access(new_dir, F_OK) == -1)
		return (write_err(new_dir, "No such file or directory"));
	if (is_directory(new_dir) == false)
		return (write_err(new_dir, "Not a directory"));
	if (access(new_dir, X_OK) == -1)
		return (write_err(new_dir, "Permission denied"));
}
