/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:35:28 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/21 21:34:40 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "execution.h"

int	execute_echo(t_list *list)
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
	return (0);
}

int	execute_cd(t_list *list)
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
	{
		perror("");
		return (1);
	}
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

void	print_export(t_env *export)
{
	(void)export;
}

//checks if the key has a value (doesnt matter if it has '=' or not)
bool	check_empty_keyvalue(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=' && arg[i + 1])
			return (false);
		i++;
	}
	return (true);
}

// //checks if the key should be exported to env (seen by '=')
// bool	export_to_env(char *arg)
// {
// 	int	i;
// 	i = 0;
// 	while (arg[i])
// 	{
// 		if (arg[i] == '=')
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

t_env	*export_empty_key(t_env **env, t_env *cur, char *name)
{
	t_env	*new;
	char	*name_copy;

	if (cur == NULL)
	{
		name_copy = ft_strdup(name);
		if (!name_copy)
			return (NULL);
		new = new_env_node(name_copy, NULL);
		if (!new)
			return (NULL);
		add_env_node_back(env, new);
	}
	else
	{
		if (cur->value)
			free(cur->value);
		cur->value = NULL;
	}
	return (*env);
}

t_env	*replace_env_value(char *arg, t_env **env, char *name)
{
	t_env	*cur;
	t_env	*prev;
	char	*value;
	int		name_len;

	cur = *env;
	while (cur)
	{
		name_len = ft_strlen(name);
		//is it also checking for the '='? if so we should not do we want to check empty var
		if (ft_strncmp(cur->name, name, name_len) == 0
		&& cur->name[name_len] == '=')
		{
			if (check_empty_keyvalue(arg) == true)
				return (export_empty_key(env, cur, name));
			value = get_env_value(arg);
			if (!value)
				return (NULL);
			if (cur->value)
				free(cur->value);
			cur->value = value;
			return (cur);
		}
		prev = cur;
		cur = cur->next;
	}
	return (NULL);
}

t_env	*create_new_variable(t_env **env, t_env *cur, char *name, char *arg)
{
	t_env	*new;
	char	*value;

	if (check_empty_keyvalue(arg) == true)
		return (export_empty_key(env, cur, name));
	value = get_env_value(arg);
	if (!value)
		return (NULL);
	new = new_env_node(name, value);
	add_env_node_back(env, new);
	return (*env);
}

int	execute_export(t_list *list, t_env **env)
{
	char	*name;
	int		i;

	if (!list->args[1])
		print_export(*env);
	i = 1;
	while (list->args[i])
	{
		name = get_env_name(list->args[i]);
		if (!name)
			return (-1);
		if (validate_export_syntax(name) == false)
		{
			write_err("export: not an identifier", name);
			return (free(name), -1);
		}
		if (replace_env_value(list->args[i], env, name) == NULL)
			create_new_variable(env, NULL, name, list->args[i]);
		free(name);
		i++;
	}
	return (0);
}

// int	execute_export(t_list *list, t_env **env)
// {
// 	t_env	*cur;
// 	t_env	*prev;
// 	char	*name;
// 	char	*value;
// 	int		i;

// 	i = 1;

// 	if (!list->args[1])
// 		print_export(*env);
// 	while (list->args[i])
// 	{
// 		cur = *env;
// 		name = get_env_name(list->args[i]);
// 		if (!name)
// 			return (-1);
// 		while (cur)
// 		{
// 			if (ft_strncmp(cur->name, name, ft_strlen(cur->name) + 1) == 0)
// 			{
// 				value = get_env_value(list->args[i]);
// 				if (!value)
// 					return (free(name), -1);
// 				free(cur->value);
// 				cur->value = value;
// 				break ;
				
// 			}
// 			prev = cur;
// 			cur = cur->next;
// 		}
// 		if (!cur)
// 		{
// 			value = get_env_value(list->args[i]);
// 			if (!value)
// 				return (free(name), -1);
// 			prev->next = new_env_node(name, value);
// 			if (!prev->next)
// 				return (free(name), free(value), -1);
// 		}
// 		free(name);
// 		free(value);
// 		i++;
// 	}
// 	return (0);
// }

int	execute_unset(t_list *list, t_env **env)
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
			return (-1);
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
	return (0);
}

int	execute_env(t_list *list, char **environment)
{
	//still need to take care of not printing variables without '='
	if (list->args[1])
		error_message("env too many arguments", -1);
	print_arr(environment);
	return (0);
}

int	execute_exit(t_list *list)
{
	(void)list;
	printf("exit\n");
	return (0);
}