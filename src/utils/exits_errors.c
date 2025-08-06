/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:38:20 by sneshev           #+#    #+#             */
/*   Updated: 2025/07/26 13:38:30 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/history.h>

void	error_message(char const *s, int exit_code)
{
	(void)exit_code;
	printf("%s\n", s);
}

void	exit_with_code(int exit_code, t_list **list_ptr, t_env **env_ptr, char **environment)
{
	free_list(list_ptr);
	free_env(env_ptr);
	free_arr(environment);
	ft_add_history(NULL, true);
	exit(exit_code % 256);
}

void	perror_message(char *s)
{
	printf("%s: command not found", s);
	printf("\n");
}

void	write_err(char *keyword, char *message)
{
	if (keyword)
	{
		write(2, keyword, ft_strlen(keyword));
		write(2, ": ", 2);
	}
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}
