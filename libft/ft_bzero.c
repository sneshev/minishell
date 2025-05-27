/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:24:57 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/21 17:10:00 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*q;

	q = (char *)s;
	while (n-- > 0)
	{
		*q = '\0';
		q++;
	}
}

// int	main()
// {
// 	char str[] = "123456";
// 	int len = 3;
// 	printf("bfr: %s\n", str);
// 	ft_bzero(str, len);
// 	printf("aftr: %s\n", str);

// 	char strr[] = "123456";
// 	printf("bfr: %s\n", strr);
// 	bzero(strr, len);
// 	printf("aftr: %s\n", strr);
// 	return (0);
// }