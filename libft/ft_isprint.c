/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:25:10 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/21 17:12:48 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c < 32)
		return (0);
	if (c > 126)
		return (0);
	return (16384);
}

// int main()
// {
//     char c = '1';
//     printf("%d\n", ft_isprint(c));
// 	printf("%d\n", isprint(c));
//     return 0;
// }