/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:59:57 by mmisumi           #+#    #+#             */
/*   Updated: 2025/06/05 12:29:55 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag_count(t_node **node)
{
	t_node	*temp;
	int		flagc;

	flagc = 0;
	temp = (*node)->next;
	while (temp && temp->arg_type == UNDEFINED)
	{
		flagc++;
		temp = temp->next;
	}
	return (flagc);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_node *list = NULL;
// 	list = create_list(&list, argv, argc - 1, envp);
// 	print_list(list);
// 	printf("flagc: %d\n", flag_count(&list));
// 	return (0);

// }

char	**get_flags(int flagc, t_node **node)
{
	char	**flags;
	int		i;

	flags = malloc(sizeof(char *) * (flagc + 1));
	if (!flags)
		return (NULL);
	i = 0;
	while (i <= flagc)
	{
		if (i == 0)
		{
			flags[i] = ft_strdup((*node)->arg);
			if (!flags[i])
				return (free_arr(flags), error_message("malloc error\n", -1), NULL);
		}
		else
		{
			flags[i] = ft_strdup((*node)->arg);
			if (!flags[i])
				return (free_arr(flags), error_message("malloc error\n", -1), NULL);
		}
		*node = (*node)->next;
		i++;
	}
	flags[i] = NULL;
	return (flags);
}

// bool	get_flags(t_node **node)
// {
// 	t_node	*temp;
// 	char	**flags;
// 	int		flagc;
// 	int		i;

// 	flagc = flag_count(node);
// 	flags = malloc(sizeof(char *) * (flagc + 1));
// 	if (!flags)
// 		return (false);
// 	i = 0;
// 	while (i <= flagc)
// 	{
// 		if (i == 0)
// 			flags[i] = temp->prev->arg;
// 		else
// 			flags[i] = temp->arg;
// 		i++;
// 	}
// 	return (*flags);
// }
