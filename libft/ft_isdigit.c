/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:25:22 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/21 17:12:44 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c < '0')
		return (0);
	if (c > '9')
		return (0);
	return (2048);
}

// int main()
// {
//     char c = '3';
//     printf("%d\n", ft_isdigit(c));
// 	printf("%d\n", isdigit(c));
//     return 0;
// }