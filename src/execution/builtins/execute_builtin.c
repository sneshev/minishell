/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:35:28 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/24 16:41:48 by mmisumi          ###   ########.fr       */
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
	//not the good error message
	if (chdir(new_dir) == -1)
		return (write_err(new_dir, "f"), 1);
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

// int	execute_unset(t_list *list, t_env **env)
// {

// }


bool	is_valid_code(char *str)
{
	int len = 0;
	char sign;

	while (is_space(*str))
		str++;
	sign = 'p';
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 'n';
		str++;
	}
	if (!*str)
		return (false);
	while(*str == '0')
		str++;
    if (!*str)
        return (true);
    while (ft_isdigit(str[len]))
        len++;
    if (str[len] != '\0')
        return (false);
    if (len > 19)
        return (false);
    if (len == 19)
    {
        if (sign == 'p' && ft_strcmp(str, "9223372036854775807") > 0)
            return (false);
        if (sign == 'n' && ft_strcmp(str, "9223372036854775808") > 0)
            return (false);
    }
    return (true);
}

int	execute_exit(t_list *list)
{
	int	arg_count;

	write(1, "exit\n", 5);
	arg_count = count_strings(list->args, true) - 1;
	// printf("arg_count: %d\n", count_strings(list->args, true));
	if (arg_count == 0)
		exit_with_code(0);
	else if (arg_count == 1)
	{
		if (is_valid_code((list->args)[1]))
			exit_with_code(ft_atol((list->args)[1]) % 256);
		else
		{
			write(1, "exit: ", 6);
			write_err((list->args)[1], "numeric argument required");
			exit_with_code(2);
		}
	}
	else
		write_err("exit", "too many arguments");
	return (1);
}
