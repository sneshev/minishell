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

int	flag_count(t_list **list)
{
	t_list	*temp;
	int		flagc;

	flagc = 1;
	temp = (*list)->next;
	while (temp && temp->arg_type != REDIRECTION && temp->arg_type != PIPE)
	{
		flagc++;
		temp = temp->next;
	}
	return (flagc);
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_list *list = NULL;
// 	list = create_list(&list, argv, argc - 1, envp);
// 	print_list(list);
// 	printf("flagc: %d\n", flag_count(&list));
// 	return (0);

// }

char	**get_flags(int flagc, t_list **list)
{
	char	**flags;
	int		i;

	flags = malloc(sizeof(char *) * (flagc + 1));
	if (!flags)
		return (NULL);
	i = 0;
	while (i < flagc)
	{
		if (i == 0)
		{
			flags[i] = ft_strdup((*list)->arg);
			if (!flags[i])
				return (free_arr(flags), error_message("malloc error\n", -1), NULL);
		}
		else
		{
			flags[i] = ft_strdup((*list)->arg);
			if (!flags[i])
				return (free_arr(flags), error_message("malloc error\n", -1), NULL);
		}
		*list = (*list)->next;
		i++;
	}
	flags[i] = NULL;
	return (flags);
}
