/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:05:58 by sneshev           #+#    #+#             */
/*   Updated: 2025/07/26 15:06:12 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "list.h"

void	free_env_node(t_env **prev_env)
{
	if (!prev_env || !*prev_env)
		return ;
	if ((*prev_env)->name)
		free((*prev_env)->name);
	if ((*prev_env)->value)
		free((*prev_env)->value);
	free(*prev_env);
	*prev_env = NULL;
}

void	free_env(t_env **env)
{
	t_env	*temp;

	if (!env)
		return ;
	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free_env_node(&temp);
	}
	*env = NULL;
}
