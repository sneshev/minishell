/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:35:28 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/24 17:18:32 by mmisumi          ###   ########.fr       */
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

	while (is_newline_flag(list->args[i]) == true)
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

void	cd_error(char *new_dir)
{
	if (access(new_dir, F_OK) == -1)
		return (write_err(new_dir, "No such file or directory"));
	if (is_directory(new_dir) == false)
		return (write_err(new_dir, "Not a directory"));
	if (access(new_dir, X_OK) == -1)
		return (write_err(new_dir, "Permission denied"));
}

int	execute_cd(t_list *list, t_env *env)
{
	char	*new_dir;
	int		i;

	new_dir = NULL;
	if (!list->args[1])
	{
		while (env)
		{
			if (ft_strcmp("HOME=", env->name) == 0)
				new_dir = env->name;
			env = env->next;
		}
	}
	i = 0;
	while (list->args[i])
		i++;
	if (i > 2)
		return (write_err("cd", "too many arguments"), 1);
	new_dir = list->args[1];
	if (chdir(new_dir) == -1)
		return (cd_error(new_dir), 1);
	return (0);
}


int	execute_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (1);
	printf("%s\n", dir);
	return (0);
}
