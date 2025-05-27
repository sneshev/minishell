/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:45:39 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/22 22:47:49 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nnod;

	nnod = malloc(sizeof(t_list));
	if (!nnod)
		return (NULL);
	nnod->content = content;
	nnod->next = NULL;
	return (nnod);
}

// int main()
// {
// 	t_list *lst;
// 	lst = ft_lstnew(strdup("bratwaaaa.."));
// 	if (!lst)
// 		return 1;

// 	t_list *second;
// 	second  = ft_lstnew(strdup("krab!"));
// 	if (!second)
// 		return 1;
// 	lst->next = second;

// 	printf("\nList size: %d\n", ft_lstsize(lst));

// 	t_list *tmp = lst;
// 	printf("1st node: %s\n", (char *)tmp->content);
// 	tmp = tmp->next;
// 	printf("2nd node: %s\n\n", (char *)tmp->content);
// 	free(lst->content);
// 	free(second->content);
// 	free(lst);
// 	free(second);

// 	return 0;
// }