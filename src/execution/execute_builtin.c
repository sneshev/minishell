/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:35:28 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/14 12:19:08 by sneshev          ###   ########.fr       */
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
			printf("%s", list->args[i]);
			i++;
			if (list->args[i])
				printf(" ");
		}
	}
	if (newline == 1)
		printf("\n");
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
		perror_message(new_dir);
}

void	execute_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	printf("%s\n", dir);
}

void	execute_export(t_list *list, t_env **env)
{
	int		i;

	i = 1;
	// we should print export variables
	if (!list->args[i])
	{
		
	}
	while (list->args[i])
	{
		create_var_node(list->args[i], env);
		i++;
	}
}

void	execute_unset(t_list *list, t_env **env)
{
	t_env	*cur;
	t_env	*prev;
	t_env	*temp;
	int		i;
	int		name_len;

	cur = *env;
	prev = NULL;
	i = 1;

	while (cur && list->args[i])
	{
		name_len = ft_strlen(cur->name);
		// printf("name_len: %d\n", name_len);
		// print_arr(list->args);
		// printf("cur->name: %s\n", cur->name);
		// printf("char: %c\n", cur->name[name_len - 1]);
		if (ft_strncmp(list->args[i], cur->name, (name_len - 1)) == 0
		&& cur->name[name_len - 1] == '=')
		{
			printf("MATCH\n");
			if (prev)
			{
				prev->next = cur->next;
				temp = cur;
				cur = cur->next;
				free_env_node(&temp);
			}
			else
			{
				*env = cur->next;
				temp = cur;
				cur = *env;
				free_env_node(&temp);
			}
			i++;
			continue ;
		}
		prev = cur;
		cur = cur->next;
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