/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:21:48 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/22 13:28:37 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (ptr[i])
		i++;
	ptr += i;
	while (i >= 0)
	{
		if ((unsigned char)*ptr == (unsigned char)c)
			return (ptr);
		i--;
		ptr--;
	}
	return (0);
}

// int main()
// {
// 	printf("%s\n", ft_strrchr("12a34512345", '1'));
// 	printf("%s\n", strrchr("12a34512345", '1'));
// }