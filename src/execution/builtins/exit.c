/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:18:14 by mmisumi           #+#    #+#             */
/*   Updated: 2025/07/26 15:46:09 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../execution.h"

bool	is_valid_code(char *str)
{
	int		len;
	char	sign;

	len = 0;
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
	while (*str == '0')
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
