/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:35:43 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/22 13:24:09 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b;
	size_t	l;

	if (!*little)
		return ((char *)big);
	b = 0;
	while (big[b] && b < len)
	{
		if (big[b] == little[0])
		{
			l = 0;
			while (big[b + l] == little[l] && (b + l) < len && little[l])
				l++;
			if (!little[l])
				return ((char *)&big[b]);
		}
		b++;
	}
	return (NULL);
}

// int main()
// {
// 	printf("%s\n", ft_strnstr("abcdef", "c", 4));
// }