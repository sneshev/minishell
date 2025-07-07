/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:35:28 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/05 16:07:45 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

void	execute_echo(t_list *list)
{
	(void)list;
	printf("echo\n");
	free_list(&list);
	return ;
}

void	execute_cd(t_list *list, t_env *env)
{
	char	*new_dir;
	int		i;

	i = 0;
	while (list->args[i])
		i++;
	if (i == 1)
	{
		while (env)
		{
			if (ft_strncmp(env->name, "HOME=", 6) == 0)
				break ;
			env = env->next;
		}
		new_dir = env->value;
	}
	else if (i == 2)
		new_dir = list->args[1];
	else
		error_message("cd invalid arg amount", -1);
	if (chdir(new_dir) == -1)
		error_message("chdir error", -1);
	return ;
}

void	execute_pwd(t_list *list)
{
	(void)list;
	printf("pwd\n");
	free_list(&list);
	return ;
}

void	execute_export(t_list *list, t_env *env)
{
	(void)list;
	(void)env;
	printf("export\n");
	free_list(&list);
	free_env(&env);
	return ;
}

void	execute_unset(t_list *list, t_env *env)
{
	(void)list;
	(void)env;
	printf("unset\n");
	free_list(&list);
	free_env(&env);
	return ;
}

void	execute_env(t_list *list, t_env *env)
{
	(void)list;
	(void)env;
	printf("env\n");
	free_list(&list);
	free_env(&env);
	return ;
}

void	execute_exit(t_list *list)
{
	(void)list;
	printf("exit\n");
	free_list(&list);
	return ;
}