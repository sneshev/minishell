/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:24:51 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/22 14:31:14 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (dest == 0 && src == 0)
		return (NULL);
	d = (char *)dest;
	s = (char *)src;
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dest);
}

// int main()
// {
// 	int n = 3;
// 	char	src[] = "123456";
// 	char	dest[n + 1];
// 	for (int i = 0; i < n + 1; i++)
// 		dest[i] = '\0';
// 	ft_memcpy(dest, src, n);
// 	printf("src: %s\n", src);
// 	printf("dest: %s\n\n", dest);
// 	char	srcc[] = "123456";
// 	char	destt[n + 1];
// 	for (int i = 0; i < n + 1; i++)
// 		destt[i] = '\0';
// 	memcpy(destt, srcc, n);
// 	printf("srcc: %s\n", srcc);
// 	printf("destt: %s\n\n", destt);
// }