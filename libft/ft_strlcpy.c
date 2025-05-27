/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:46:12 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/21 17:15:00 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	l;
	size_t	i;

	l = 0;
	i = 0;
	while (src[l])
		l++;
	if (size > 0)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (l);
}

// int main()
// {
// 	char src[] = "123456";
// 	int len = sizeof(src);
// 	char dest[len];
// 	printf("len: %d, ", ft_strlcpy(dest, src, 572));
// 	printf("dst: %s\n", dest);

// 	char srcc[] = "123456";
// 	int lenn = sizeof(srcc);
// 	char destt[lenn];
// 	printf("len: %d, ", strlcpy(destt, srcc, 572));
// 	printf("dstt: %s\n", destt);
// }