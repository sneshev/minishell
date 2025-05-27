/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:29:04 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/21 17:12:55 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*ptr;

	ptr = (const char *)s;
	while (n > 0)
	{
		if (*ptr == (const char)c)
			return ((void *)ptr);
		n--;
		ptr++;
	}
	return (0);
}

// int main()
// {
// 	char str[] = "12345c";
// 	printf("%p\n", str + 5);
// 	printf("%p\n", ft_memchr(str, 'c', 7));
// 	printf("%p\n", memchr(str, 'c', 7));
// }