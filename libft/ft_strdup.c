/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:04:37 by sneshev           #+#    #+#             */
/*   Updated: 2024/10/21 17:14:25 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	i = 0;
	len = 1;
	while (s[len - 1])
		len++;
	ptr = malloc(len);
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}
// int main()
// {
// 	char str[] = "okrr";
// 	char *ptr = ft_strdup(str);
// 	if (ptr == NULL)
// 	{
// 		printf("Uh-oh..");
// 		return 1;
// 	}
// 	printf("%p\n%p\n", str, ptr);
//	free(ptr);
// 	printf("%s", ptr);
// }