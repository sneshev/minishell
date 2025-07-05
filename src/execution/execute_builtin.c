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
	exit(1);
}

void	execute_cd(t_list *list)
{
	(void)list;
	printf("cd\n");
	free_list(&list);
	exit(1);
}

void	execute_pwd(t_list *list)
{
	(void)list;
	printf("pwd\n");
	free_list(&list);
	exit(1);
}

void	execute_export(t_list *list, t_env *env)
{
	(void)list;
	(void)env;
	printf("export\n");
	free_list(&list);
	free_env(&env);
	exit(1);
}

void	execute_unset(t_list *list, t_env *env)
{
	(void)list;
	(void)env;
	printf("unset\n");
	free_list(&list);
	free_env(&env);
	exit(1);
}

void	execute_env(t_list *list, t_env *env)
{
	(void)list;
	(void)env;
	printf("env\n");
	free_list(&list);
	free_env(&env);
	exit(1);
}

void	execute_exit(t_list *list)
{
	(void)list;
	printf("exit\n");
	free_list(&list);
	exit(1);
}