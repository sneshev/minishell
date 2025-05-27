/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:11:47 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/22 22:35:37 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

// int main()
// {
// 	t_list	*lst;
// 	lst = malloc(sizeof(t_list));
// 	if (!lst)
// 		return 1;
// 	lst->content = (char *)malloc((strlen("bratwaaaa..") + 1) * sizeof(char));
// 	if (!lst->content)
// 		return 1;
// 	strcpy(lst->content, "bratwaaaa..");
// 	lst->next = malloc(sizeof(t_list));
// 	if (!lst->next)
// 		return 1;
// 	lst->next->content = (char *)malloc((strlen("krab!") + 1) * sizeof(char));
// 	strcpy(lst->next->content, "krab!");
// 	lst->next->next = NULL;
// 	printf("%d\n", ft_lstsize(lst));
// }