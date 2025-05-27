/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:24:43 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/22 14:28:48 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (dest == 0 && src == 0)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (s < d)
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	else
	{
		while (n-- > 0)
			*d++ = *s++;
	}
	return (dest);
}

// int main()
// {
// 	char	src1[] = "123456";
// 	char	src2[] = "123456";
// 	printf("\nsrc1: %s\n", src1);
// 	printf("src2: %s\n", src2);
// 	ft_memmove(src1, src1 + 2, 1);
// 	printf("\nsrc1: %s\n", src1);
// 	memmove(src2, src2 + 2, 1);
// 	printf("src2: %s\n", src2);
// }