/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:25:25 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/21 17:10:16 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c < 'A')
		return (0);
	if (c > 'Z' && c < 'a')
		return (0);
	if (c > 'z')
		return (0);
	return (1024);
}

// int main()
// {
//     char c = 'a';
//     printf("%d\n", ft_isalpha(c));
// 	printf("%d\n", isalpha(c));
//     return 0;
// }