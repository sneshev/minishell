/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:10:43 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/22 13:26:35 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if ((unsigned char)c == (unsigned char)*ptr)
			return (ptr);
		ptr++;
	}
	if ((unsigned char)*ptr == (unsigned char)c)
		return (ptr);
	return (0);
}

// int main()
// {
// 	char str[] = "abcdeffff";
// 	char c = 'f';
// 	printf("%s\n", ft_strchr(str, c));
// 	printf("%s\n", strchr(str, c));
// }