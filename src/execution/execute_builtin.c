/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:35:28 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/16 17:56:38 by mmisumi          ###   ########.fr       */
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
		new_dir = getenv("HOME");
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
	t_env	*cur;
	t_env	*prev;
	char	*name;
	char	*value;
	int		i;

	i = 1;
	while (list->args[i])
	{
		cur = *env;
		name = get_env_name(list->args[i]);
		if (!name)
			return ;
		while (cur)
		{
			if (ft_strncmp(cur->name, name, ft_strlen(cur->name) + 1) == 0)
			{
				value = get_env_value(list->args[i]);
				if (!value)
					return (free(name));
				free(cur->value);
				cur->value = value;
				break ;
				
			}
			prev = cur;
			cur = cur->next;
		}
		if (!cur)
		{
			value = get_env_value(list->args[i]);
			if (!value)
				return (free(name));
			prev->next = new_env_node(name, value);
			if (!prev->next)
				return (free(name), free(value));
		}
		i++;
	}
}

void	execute_unset(t_list *list, t_env **env)
{
	t_env	*cur;
	t_env	*prev;
	t_env	*temp;
	char	*name;
	int		i;

	i = 1;
	while (list->args[i])
	{
		cur = *env;
		prev = NULL;
		name = get_env_name(list->args[i]);
		if (!name)
			return ;
		while (cur)
		{
			if (ft_strncmp(cur->name, name, ft_strlen(name)) == 0
			&& cur->name[ft_strlen(name)] == '=')
			{
				if (prev)
				{
					prev->next = cur->next;
					temp = cur;
					cur = cur->next;
				}
				else
				{
					*env = cur->next;
					temp = cur;
					cur = *env;
				}
				free_env_node(&temp);
				break ;
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
	free(name);
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
	return ;
}