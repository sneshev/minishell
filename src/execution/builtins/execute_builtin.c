/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:35:28 by mmisumi           #+#    #+#             */
/*   Updated: 2025/09/10 15:58:29 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../execution.h"

int	execute_echo(t_list *list)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (list->args[i] && is_newline_flag(list->args[i]) == true)
	{
		newline = 0;
		i++;
	}
	while (list->args[i])
	{
		printf("%s", list->args[i]);
		i++;
		if (list->args[i])
			printf(" ");
	}
	if (newline == 1)
		printf("\n");
	return (0);
}

int	execute_cd(t_list *list, t_env *env)
{
	char	*new_dir;
	char	*new_pwd;
	char	*old_pwd;

	new_pwd = NULL;
	old_pwd = NULL;
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	if (update_pwd(env, "OLDPWD=", &old_pwd) == 1)
		free(new_pwd);
	if (!list->args[0] || !list->args[1])
		return (write_err("cd", "too little arguments"), 1);
	if (list->args[2])
		return (write_err("cd", "too many arguments"), 1);
	new_dir = list->args[1];
	if (chdir(new_dir) == -1)
		return (cd_error(new_dir), 1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (1);
	if (update_pwd(env, "PWD=", &new_pwd) == 1)
		free(new_pwd);
	return (0);
}

int	execute_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (1);
	printf("%s\n", dir);
	free(dir);
	return (0);
}
