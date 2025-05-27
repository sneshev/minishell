/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:13:34 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/21 17:14:57 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	i = 0;
	dst_len = 0;
	src_len = 0;
	while (dst[dst_len] && dst_len < size)
		dst_len++;
	while (src[src_len])
		src_len++;
	if (size <= dst_len)
		return (size + src_len);
	while (src[i] && (dst_len + i + 1) < size)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// int main()
// {
// 	char src1[] = "12345";
// 	char srcc[] = "12345";
// 	char dest1[10] = "abc";
// 	char destt[10] = "abc";
// 	size_t	size = 17;
// 	printf("len1 = %zu\n", ft_strlcat(dest1, src1, size));
// 	printf("lenn = %zu\n", strlcat(destt, srcc, size));
// 	printf("src1 = %s\n", src1);
// 	printf("srcc = %s\n", srcc);
// 	printf("dest1 = %s\n", dest1);
// 	printf("destt = %s\n", destt);
// }
// //cc -lbsd 11strlcat.c