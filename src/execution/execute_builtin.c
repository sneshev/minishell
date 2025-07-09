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
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (list && (ft_strncmp(list->args[i], "-n", 3) == 0))
	{
		i++;
		newline = 0;
	}
	if (list)
	{
		while (list->args[i])
		{
			ft_printf("%s", list->args[i]);
			i++;
			if (list->args[i])
				ft_printf(" ");
		}
	}
	if (newline == 1)
		ft_printf("\n");
}

void	execute_cd(t_list *list)
{
	char	*new_dir;
	int		i;

	i = 0;
	while (list->args[i])
		i++;
	if (i == 1)
	{
		new_dir = getenv("HOME=");
		if (!new_dir)
			error_message("malloc error", -1);
	}
	else
		new_dir = list->args[1];
	if (chdir(new_dir) == -1)
		error_message("chdir error", -1);
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

// WRONG	
void	execute_unset(t_list *list, t_env **env)
{
	t_env	*temp;
	t_env	*to_delete;
	int		i;

	temp = *env;
	i = 1;
	while (temp)
	{
		temp = *env;
		if (ft_strncmp(list->args[i], (*env)->name, ft_strlen((*env)->name) - 1) == 0)
		{
			to_delete = temp;
			if (!temp->prev)
				*env = to_delete->next;
			else
				to_delete->prev->next = to_delete->next;
			if (to_delete->next)
				to_delete->next->prev = to_delete->prev;
			free_env_node(&to_delete);
			break ;
		}
		if (temp)
			temp = temp->next;
		i++;
	}
}

void	execute_env(t_list *list, char **environment)
{
	if (list->args[1])
		error_message("env too many arguments", -1);
	print_arr(environment);
}

void	execute_exit(t_list *list)
{
	(void)list;
	printf("exit\n");
	free_list(&list);
	return ;
}