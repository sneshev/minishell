/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code_addr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:39:49 by sneshev           #+#    #+#             */
/*   Updated: 2025/07/26 15:41:06 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	*exit_code_addr(void)
{
	static int	exit_code = 0;

	return (&exit_code);
}

void	set_exit_code(int new_code)
{
	int	*exit_code_ptr;

	exit_code_ptr = exit_code_addr();
	*exit_code_ptr = new_code;
}

int	get_exit_code(void)
{
	return (*(exit_code_addr()));
}
