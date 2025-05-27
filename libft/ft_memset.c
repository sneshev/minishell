/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:25:01 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/21 17:13:54 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*q;

	q = (char *)s;
	while (n > 0)
	{
		*q = c;
		q++;
		n--;
	}
	return (s);
}

// int	main()
// {
// 	char str[] = "123456";
// 	int len = sizeof(str);
// 	printf("bfr: %s\n", str);
// 	ft_memset(str, 97, len);
// 	printf("aftr: %s\n", str);

// 	char strr[] = "123456";
// 	printf("bfr: %s\n", strr);
// 	memset(strr, 97, len);
// 	printf("aftr: %s\n", strr);
// 	return (0);
// }