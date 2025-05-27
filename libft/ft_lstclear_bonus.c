/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:43:12 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/26 19:08:44 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*la;
	t_list	*lb;

	if (!lst || !*lst || !del)
		return ;
	la = *lst;
	while (la->next != NULL)
	{
		lb = la->next;
		del(la->content);
		free(la);
		la = lb;
	}
	del(la->content);
	free(la);
	*lst = NULL;
}
